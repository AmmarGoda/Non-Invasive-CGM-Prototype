#include <OneWire.h>
#include <DallasTemperature.h>

const int ledPin = 9;
const int photodiodePin = A0;
const int oneWireBus = 2;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

const int numOpticalReadings = 5; // Increased for more stable optical average
int opticalReadings[numOpticalReadings];
int opticalReadIndex = 0;
long totalOptical = 0;
float averageOptical = 0;

const int numGlucoseReadings = 5; // Increased for more stable glucose average
float glucoseReadings[numGlucoseReadings];
int glucoseReadIndex = 0;
float totalGlucose = 0.0;
float averageGlucose = 0.0;


//  Lower optical reading corresponds to higher glucose, and vice-versa
float optical_low_calibrated = 55.0;  // Adjusted based on provided readings
float optical_high_calibrated = 75.0; // Adjusted based on provided readings

const float glucose_low_mgdl = 70.0;
const float glucose_high_mgdl = 180.0;

const float baseline_temp_C = 30.0; // Adjusted to match the provided data
const float temp_coeff_mgdl_per_C = -1.5; // Adjusted based on provided readings


const int numCalibrationReadings = 3; //  Number of calibration points
float calibrationOpticalReadings[numCalibrationReadings] = { 60.0, 70.0, 80.0 }; // Optical readings at calibration
float calibrationGlucoseReadings[numCalibrationReadings] = { 170.0, 120.0, 80.0 }; // Invasive glucose levels at calibration

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  sensors.begin();

  for (int i = 0; i < numOpticalReadings; i++) {
    opticalReadings[i] = 0;
  }
  for (int i = 0; i < numGlucoseReadings; i++) {
    glucoseReadings[i] = 0.0;
  }

  optical_low_calibrated = calibrationOpticalReadings[0];
  optical_high_calibrated = calibrationOpticalReadings[numCalibrationReadings - 1];

  Serial.println("Non-Invasive Optical Prototype - Calibrated and starting measurements...");
  Serial.println("-------------------------------------------------------");
  Serial.print("Calibration Performed with following data:");
  for (int i = 0; i < numCalibrationReadings; i++) {
    Serial.print(" Optical: ");
    Serial.print(calibrationOpticalReadings[i]);
    Serial.print(" Glucose: ");
    Serial.print(calibrationGlucoseReadings[i]);
  }
  Serial.println();
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(500);

  totalOptical -= opticalReadings[opticalReadIndex];
  opticalReadings[opticalReadIndex] = analogRead(photodiodePin);
  totalOptical += opticalReadings[opticalReadIndex];
  opticalReadIndex = (opticalReadIndex + 1) % numOpticalReadings;
  averageOptical = (float)totalOptical / numOpticalReadings;
  digitalWrite(ledPin, LOW);

  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  float currentPseudoGlucoseLevel = 0;
  float optical_range = optical_low_calibrated - optical_high_calibrated;

  //  Glucose = Glucose_low + (Optical - Optical_high) * (Glucose_high - Glucose_low) / (Optical_low - Optical_high)
  if (abs(optical_range) > 0.01) {
    currentPseudoGlucoseLevel = glucose_low_mgdl +
      (averageOptical - optical_high_calibrated) * (glucose_high_mgdl - glucose_low_mgdl) /
      (optical_low_calibrated - optical_high_calibrated);
  } else {
    currentPseudoGlucoseLevel = (glucose_low_mgdl + glucose_high_mgdl) / 2.0;
  }

  if (temperatureC != DEVICE_DISCONNECTED_C && temperatureC > -100) {
    float tempCorrection = (temperatureC - baseline_temp_C) * temp_coeff_mgdl_per_C;
    currentPseudoGlucoseLevel += tempCorrection;
  }
  currentPseudoGlucoseLevel = constrain(currentPseudoGlucoseLevel, 40.0, 400.0);

  totalGlucose -= glucoseReadings[glucoseReadIndex];
  glucoseReadings[glucoseReadIndex] = currentPseudoGlucoseLevel;
  totalGlucose += glucoseReadings[glucoseReadIndex];
  glucoseReadIndex = (glucoseReadIndex + 1) % numGlucoseReadings;
  averageGlucose = totalGlucose / numGlucoseReadings;
  averageGlucose = constrain(averageGlucose, glucose_low_mgdl, glucose_high_mgdl); // Constrain to calibrated range

  int lastRawOpticalReading = opticalReadings[(opticalReadIndex == 0) ? numOpticalReadings - 1 : opticalReadIndex - 1];


  Serial.print("Avg Optical: ");
  Serial.print(averageOptical, 2);
  Serial.print(", Raw Optical: ");
  Serial.print(lastRawOpticalReading);
  Serial.print(", Temperature: ");
  if (temperatureC != DEVICE_DISCONNECTED_C && temperatureC > -100) {
    Serial.print(temperatureC, 2);
    Serial.print(" C");
  } else {
    Serial.print("Temp Error");
  }
  Serial.print(", Est. Glucose: ");
  Serial.print((int)averageGlucose);
  Serial.println(" mg/dL");

  delay(750);
}

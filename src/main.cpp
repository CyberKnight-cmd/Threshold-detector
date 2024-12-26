#include <Arduino.h>

# define LED_PIN 9
#define SOUND_SENSOR_PIN A0 // Analog Output pin for KY-037
#define CLAP_THRESHOLD_MULTIPLIER 2 // Multiplier to define clap threshold
#define BASELINE_MEASURE_DURATION 5000 // Duration to measure baseline (in ms)

int baselineLevel = 0; // Variable to store calculated baseline level
int clapThreshold = 0; // Variable to store calculated clap threshold

// Function to calculate the baseline noise level
int calculateBaseline(int duration) {
  long startTime = millis();
  long totalSound = 0;
  int readings = 0;

  while (millis() - startTime < duration) {
    totalSound += analogRead(SOUND_SENSOR_PIN);
    readings++;
    delay(10); // Small delay between readings
  }

  return totalSound / readings; // Return average sound level
}

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(LED_PIN, OUTPUT);
  pinMode(SOUND_SENSOR_PIN, INPUT);

  Serial.println("Measuring background noise...");
  baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION);
  clapThreshold = baselineLevel * CLAP_THRESHOLD_MULTIPLIER;

  Serial.print("Baseline Level: ");
  Serial.println(baselineLevel);
  Serial.print("Clap Threshold: ");
  Serial.println(clapThreshold);
  delay(500);
}

void loop() {
  int soundLevel = analogRead(SOUND_SENSOR_PIN); // Read current sound level

  if (soundLevel > clapThreshold) { // Detect clap based on threshold
    Serial.println("Clap Detected!");
    digitalWrite(LED_PIN, HIGH);
    delay(90); // Add delay to avoid multiple detections for a single clap
    digitalWrite(LED_PIN, LOW);
  }
}



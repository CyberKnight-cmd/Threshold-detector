// #include <Arduino.h>

// # define LED_PIN 9
// #define SOUND_SENSOR_PIN A0 // Analog Output pin for KY-037
// #define CLAP_THRESHOLD_MULTIPLIER 2 // Multiplier to define clap threshold
// #define BASELINE_MEASURE_DURATION 10000// Duration to measure baseline (in ms)

// int baselineLevel = 0; // Variable to store calculated baseline level
// int clapThreshold = 0; // Variable to store calculated clap threshold

// // Function to calculate the baseline noise level
// int calculateBaseline(int duration) {
//   long startTime = millis();
//   long totalSound = 0;
//   int readings = 0;

//   while (millis() - startTime < duration) {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     readings++;
//     delay(10); // Small delay between readings
//   }

//   return totalSound / readings; // Return average sound level
// }

// void setup() {
//   Serial.begin(9600); // Initialize serial communication
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN,HIGH);
//   pinMode(SOUND_SENSOR_PIN, INPUT);
//   digitalWrite(LED_PIN,LOW);

//   digitalWrite(LED_PIN,HIGH);
//   Serial.println("Measuring background noise...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION);
//   digitalWrite(LED_PIN,LOW);
//   clapThreshold = baselineLevel * CLAP_THRESHOLD_MULTIPLIER;

//   digitalWrite(LED_PIN,HIGH);
//   Serial.print("Baseline Level: ");
//   Serial.println(baselineLevel);
//   Serial.print("Clap Threshold: ");
//   Serial.println(clapThreshold);

//   delay(500);
//   digitalWrite(LED_PIN,LOW);
// }

// void loop() {
//   int soundLevel = analogRead(SOUND_SENSOR_PIN); // Read current sound level

//   if (soundLevel > clapThreshold) { // Detect clap based on threshold
//     Serial.println("Clap Detected!");
//     digitalWrite(LED_PIN, HIGH);
//     delay(90); // Add delay to avoid multiple detections for a single clap
//     digitalWrite(LED_PIN, LOW);
//   }
// }

// #include <Arduino.h>

// #define SOUND_SENSOR_PIN A0            // Analog Output pin for KY-037
// #define BASELINE_MEASURE_DURATION 5000 // Duration to measure baseline (in ms)
// #define CHANGE_THRESHOLD_FOR_COLUMMN_ONE 1
// #define CHANGE_THRESHOLD_FOR_COLUMMN_TWO 2
// #define CHANGE_THRESHOLD_FOR_COLUMMN_THREE 3


// int firstColumn = 9;
// int secondColumn = 8;
// int thirdColumn = 7;
// int baselineLevel = 0;       // Stores the baseline sound level
// int previousSoundLevel = -1; // Stores the previous sound level

// // Function to calculate the baseline noise level
// int calculateBaseline(int duration)
// {
//   long startTime = millis();
//   long totalSound = 0;
//   int readings = 0;

//   while (millis() - startTime < duration)
//   {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     readings++;
//     delay(10); // Small delay between readings
//   }

//   return totalSound / readings; // Return average sound level
// }

// void columnOne(int value)
// {
//   if (value == 0)
//     digitalWrite(firstColumn, LOW);
//   else
//     digitalWrite(firstColumn, HIGH);
// }

// void columnTwo(int value)
// {
//   if (value == 0)
//     digitalWrite(secondColumn, LOW);
//   else
//     digitalWrite(secondColumn, HIGH);
// }

// void columnThree(int value)
// {
//   if (value == 0)
//     digitalWrite(thirdColumn, LOW);
//   else
//     digitalWrite(thirdColumn, HIGH);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
//   columnOne(1);
//   columnTwo(1);
//   columnThree(1);
//   Serial.begin(9600); // Initialize serial communication
//   pinMode(SOUND_SENSOR_PIN, INPUT);

//   Serial.println("Initializing... Measuring background noise levels...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline
//   previousSoundLevel = baselineLevel;                           // Initialize previous sound level to baseline

//   Serial.print("Baseline Level Established: ");
//   Serial.println(baselineLevel);
//   Serial.println("Monitoring sound level changes...");
  
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);
// }

// void loop()
// {

//   int currentSoundLevel = analogRead(SOUND_SENSOR_PIN); // Read current sound level
  
//   // Check if the sound level has changed significantly
//   int changeFromBaseline = currentSoundLevel - baselineLevel;
//   if (changeFromBaseline > 0)
//   {
//     Serial.print("Sound Level Changed : ");
//     Serial.print(currentSoundLevel);
//     if (changeFromBaseline >= CHANGE_THRESHOLD_FOR_COLUMMN_THREE)
//     {
//       columnThree(1);
//       columnTwo(1);
//       columnOne(1);
//     }
//     if (changeFromBaseline >= CHANGE_THRESHOLD_FOR_COLUMMN_TWO)
//     {
//       columnTwo(1);
//       columnOne(1);
//     }
//     else if (changeFromBaseline >= CHANGE_THRESHOLD_FOR_COLUMMN_ONE)
//     {
//       columnOne(1);
//     }
//     delay(5000);
//   }
//   else{
//   Serial.print("Current Sound Level : ");
//   Serial.println(currentSoundLevel);
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);
//   delay(100);
//   }
// }

// #include<Arduino.h>

// int firstColumn = 9;
// int secondColumn = 8;
// int thirdColumn = 7;

// void columnOne(int value){
//   if (value==0)
//     digitalWrite(firstColumn, LOW);
//   else
//     digitalWrite(firstColumn, HIGH);
// }

// void columnTwo(int value){
//   if (value==0)
//     digitalWrite(secondColumn, LOW);
//   else
//     digitalWrite(secondColumn, HIGH);
// }

// void columnThree(int value){
//   if (value==0)
//     digitalWrite(thirdColumn, LOW);
//   else
//     digitalWrite(thirdColumn, HIGH);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
// }

// void loop()
// {
//   columnOne(1);
//   delay(50);
//   columnTwo(1);
//   delay(50);
//   columnThree(1);
//   delay(50);
//   columnOne(0);
//   delay(50);
//   columnTwo(0);
//   delay(50);
//   columnThree(0);
//   delay(50);
// }




// #include <Arduino.h>

// #define SOUND_SENSOR_PIN A0            // Analog Output pin for KY-038
// #define BASELINE_MEASURE_DURATION 5000 // Duration to measure baseline (in ms)
// #define NUM_SAMPLES 50                // Number of samples for smoothing

// int firstColumn = 9;
// int secondColumn = 8;
// int thirdColumn = 7;
// float baselineLevel = 0.0;  // Stores the baseline sound level
// float previousSoundLevel = -1.0; // Stores the previous sound level

// // Function to calculate the baseline noise level
// float calculateBaseline(unsigned long duration)
// {
//     unsigned long startTime = millis();
//     float totalSound = 0.0;
//     int readings = 0;

//     while (millis() - startTime < duration)
//     {
//         totalSound += analogRead(SOUND_SENSOR_PIN);
//         readings++;
//         delay(10); // Small delay between readings
//     }

//     return totalSound / readings / 1023.0 * 5.0; // Return average sound level in volts
// }

// // Function to read and smooth sound level
// float smoothReading(int pin, int samples)
// {
//     float total = 0.0;
//     for (int i = 0; i < samples; i++)
//     {
//         total += analogRead(pin);
//         delay(10);
//     }
//     return (total / samples) / 1023.0 * 5.0; // Return average voltage level
// }

// void columnOne(int value)
// {
//     digitalWrite(firstColumn, value ? HIGH : LOW);
// }

// void columnTwo(int value)
// {
//     digitalWrite(secondColumn, value ? HIGH : LOW);
// }

// void columnThree(int value)
// {
//     digitalWrite(thirdColumn, value ? HIGH : LOW);
// }

// void setup()
// {
//     pinMode(firstColumn, OUTPUT);
//     pinMode(secondColumn, OUTPUT);
//     pinMode(thirdColumn, OUTPUT);
//     columnOne(1);
//     columnTwo(1);
//     columnThree(1);
//     Serial.begin(9600); // Initialize serial communication
//     pinMode(SOUND_SENSOR_PIN, INPUT);

//     Serial.println("Initializing... Measuring background noise levels...");
//     baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline
//     previousSoundLevel = baselineLevel;                           // Initialize previous sound level to baseline

//     Serial.print("Baseline Level Established: ");
//     Serial.println(baselineLevel, 4);  // Print with 4 decimal precision for clarity
//     Serial.println("Monitoring sound level changes...");

//     columnOne(0);
//     columnTwo(0);
//     columnThree(0);
// }

// void loop()
// {
//     float currentSoundLevel = smoothReading(SOUND_SENSOR_PIN, NUM_SAMPLES); // Read and smooth sound level

//     Serial.print("Current Sound Level (V): ");
//     Serial.println(currentSoundLevel, 4); // Print with 4 decimal precision

//     // Check if the sound level has changed significantly
//     float changeFromBaseline = currentSoundLevel - baselineLevel;

//     if (changeFromBaseline > 0.0)
//     {
//         Serial.print("Sound Level Change: ");
//         Serial.println(changeFromBaseline, 4);

//         if (changeFromBaseline >= 1.0)  // Set threshold as needed
//         {
//             columnThree(1);
//             columnTwo(1);
//             columnOne(1);
//         }
//         else if (changeFromBaseline >= 0.5)
//         {
//             columnTwo(1);
//             columnOne(1);
//         }
//         else if (changeFromBaseline >= 0.2)
//         {
//             columnOne(1);
//         }

//         delay(500); // Optional: Delay for responsiveness, adjust as needed
//     }
//     else
//     {
//         Serial.println("No significant change.");
//         columnOne(0);
//         columnTwo(0);
//         columnThree(0);
//         delay(100); // Small delay for responsiveness
//     }
// }




// #include <Arduino.h>

// #define SOUND_SENSOR_PIN A0            // Analog Output pin for KY-037
// #define BASELINE_MEASURE_DURATION 5000 // Duration to measure baseline (in ms)
// #define CHANGE_THRESHOLD_LOW 0.5    // Threshold for mild noise (Low light)
// #define CHANGE_THRESHOLD_MEDIUM 1.5 // Threshold for medium noise (Flicker)
// #define CHANGE_THRESHOLD_HIGH 2.5   // Threshold for high noise (Flash)

// int firstColumn = 9;   // Low intensity light (mild glow)
// int secondColumn = 8;  // Medium intensity light (flicker)
// int thirdColumn = 7;   // High intensity light (flash)

// float baselineLevel = 0.0; // Stores the baseline sound level

// // Function to calculate the baseline noise level
// float calculateBaseline(int duration)
// {
//   long startTime = millis();
//   long totalSound = 0;
//   int readings = 0;

//   while (millis() - startTime < duration)
//   {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     readings++;
//     delay(10); // Small delay between readings
//   }

//   return (float)totalSound / readings; // Return average sound level
// }

// // Function to calculate the moving average of the last N readings
// float getAverageReading(int numReadings)
// {
//   long totalSound = 0;
//   for (int i = 0; i < numReadings; i++)
//   {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     delay(10); // Small delay between readings
//   }
//   return (float)totalSound / numReadings;
// }

// void columnOne(int value) // Low intensity light
// {
//   if (value == 0)
//     digitalWrite(firstColumn, LOW);
//   else
//     digitalWrite(firstColumn, HIGH);
// }

// void columnTwo(int value) // Medium intensity light
// {
//   if (value == 0)
//     digitalWrite(secondColumn, LOW);
//   else
//     digitalWrite(secondColumn, HIGH);
// }

// void columnThree(int value) // High intensity light
// {
//   if (value == 0)
//     digitalWrite(thirdColumn, LOW);
//   else
//     digitalWrite(thirdColumn, HIGH);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);

//   Serial.begin(9600); // Initialize serial communication
//   pinMode(SOUND_SENSOR_PIN, INPUT);

//   Serial.println("Initializing... Measuring background noise levels...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline

//   Serial.print("Baseline Level Established: ");
//   Serial.println(baselineLevel);
//   Serial.println("Monitoring sound level changes...");
// }

// void loop()
// {
//   // Get the average reading of the last 5 sound sensor values to smooth the data
//   float currentSoundLevel = getAverageReading(5); 

//   // Calculate the change from baseline (positive or negative)
//   float changeFromBaseline = currentSoundLevel - baselineLevel;

//   // Monitor if the sound level has increased significantly
//   if (changeFromBaseline > 0)
//   {
//     Serial.print("Sound Level Changed: ");
//     Serial.print(currentSoundLevel);
//     Serial.print(" | Change from Baseline: ");
//     Serial.println(changeFromBaseline);

//     // Adjust lighting based on thresholds
//     if (changeFromBaseline >= CHANGE_THRESHOLD_HIGH) 
//     {
//       // High noise: Flash the third column (maximum light)
//       columnThree(1);
//       columnTwo(0);
//       columnOne(0);
//     }
//     else if (changeFromBaseline >= CHANGE_THRESHOLD_MEDIUM)
//     {
//       // Medium noise: Flicker the second column (medium light)
//       columnThree(0);
//       columnTwo(1);
//       columnOne(0);
//     }
//     else if (changeFromBaseline >= CHANGE_THRESHOLD_LOW)
//     {
//       // Low noise: Low glow on the first column (mild light)
//       columnThree(0);
//       columnTwo(0);
//       columnOne(1);
//     }
//     delay(500);  // Small delay for better stability
//   }
//   else
//   {
//     // No significant change: Turn off lights
//     Serial.print("Current Sound Level: ");
//     Serial.println(currentSoundLevel);
//     columnOne(0);
//     columnTwo(0);
//     columnThree(0);
//     delay(200);  // Small delay for lower power consumption when idle
//   }
// }










// A better approach







// #include <Arduino.h>

// #define SOUND_SENSOR_PIN A0              // Analog Output pin for KY-037
// #define BASELINE_MEASURE_DURATION 5000   // Duration to measure baseline (in ms)
// #define CHANGE_THRESHOLD 0.005           // Threshold for detecting a fluctuation
// #define FLUCTUATION_WINDOW 1000          // Duration for counting fluctuations (in ms)
// #define FLUCTUATION_COUNT_LOW 3          // Low fluctuation threshold (e.g., 3 fluctuations)
// #define FLUCTUATION_COUNT_MEDIUM 5       // Medium fluctuation threshold (e.g., 6 fluctuations)
// #define FLUCTUATION_COUNT_HIGH 8        // High fluctuation threshold (e.g., 10 fluctuations)

// int firstColumn = 9;   // Low intensity light (mild glow)
// int secondColumn = 8;  // Medium intensity light (flicker)
// int thirdColumn = 7;   // High intensity light (flash)

// float baselineLevel = 0.0; // Stores the baseline sound level

// // Function to calculate the baseline noise level
// float calculateBaseline(int duration)
// {
//   long startTime = millis();
//   long totalSound = 0;
//   int readings = 0;

//   while (millis() - startTime < duration)
//   {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     readings++;
//     delay(10); // Small delay between readings
//   }

//   return (float)totalSound / readings; // Return average sound level
// }

// // Function to count fluctuations in the sound level within a window
// int countFluctuations(int duration, float threshold)
// {
//   long startTime = millis();
//   int fluctuationCount = 0;
//   float lastReading = analogRead(SOUND_SENSOR_PIN);
  
//   while (millis() - startTime < duration)
//   {
//     float currentReading = analogRead(SOUND_SENSOR_PIN);
//     if (abs(currentReading - lastReading) > threshold) // Check for a significant change
//     {
//       fluctuationCount++;
//     }
//     lastReading = currentReading;
//     delay(10); // Small delay between readings
//   }

//   return fluctuationCount;
// }

// void columnOne(int value) // Low intensity light
// {
//   if (value == 0)
//     digitalWrite(firstColumn, LOW);
//   else
//     digitalWrite(firstColumn, HIGH);
// }

// void columnTwo(int value) // Medium intensity light
// {
//   if (value == 0)
//     digitalWrite(secondColumn, LOW);
//   else
//     digitalWrite(secondColumn, HIGH);
// }

// void columnThree(int value) // High intensity light
// {
//   if (value == 0)
//     digitalWrite(thirdColumn, LOW);
//   else
//     digitalWrite(thirdColumn, HIGH);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);

//   Serial.begin(9600); // Initialize serial communication
//   pinMode(SOUND_SENSOR_PIN, INPUT);

//   Serial.println("Initializing... Measuring background noise levels...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline

//   Serial.print("Baseline Level Established: ");
//   Serial.println(baselineLevel);
//   Serial.println("Monitoring sound level changes...");
// }

// void loop()
// {
//   // Count fluctuations in sound level within the defined time window
//   int fluctuationCount = countFluctuations(FLUCTUATION_WINDOW, CHANGE_THRESHOLD); 

//   // Monitor if the fluctuation count indicates significant noise
//   Serial.print("Fluctuations in the last ");
//   Serial.print(FLUCTUATION_WINDOW / 1000);
//   Serial.print(" second(s): ");
//   Serial.println(fluctuationCount);

//   // Adjust lighting based on fluctuation count
//   if (fluctuationCount >= FLUCTUATION_COUNT_HIGH)
//   {
//     // High noise: Flash the third column (maximum light)
//     columnThree(1);
//     columnTwo(0);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_MEDIUM)
//   {
//     // Medium noise: Flicker the second column (medium light)
//     columnThree(0);
//     columnTwo(1);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_LOW)
//   {
//     // Low noise: Low glow on the first column (mild light)
//     columnThree(0);
//     columnTwo(0);
//     columnOne(1);
//   }
//   else
//   {
//     // No significant fluctuations: Turn off lights
//     columnOne(0);
//     columnTwo(0);
//     columnThree(0);
//   }

//   delay(250);  // Small delay for better stability
// }






















// #include <Arduino.h>

// #define SOUND_SENSOR_PIN A0              // Analog Output pin for KY-037
// #define BASELINE_MEASURE_DURATION 5000   // Duration to measure baseline (in ms)
// #define CHANGE_THRESHOLD 1.9        // Increased threshold for detecting a fluctuation
// #define FLUCTUATION_WINDOW 2000          // Duration for counting fluctuations (in ms)
// // #define FLUCTUATION_COUNT_LOW 30       // Low fluctuation threshold (e.g., 3 fluctuations)
// // #define FLUCTUATION_COUNT_MEDIUM 50       // Medium fluctuation threshold (e.g., 6 fluctuations)
// // #define FLUCTUATION_COUNT_HIGH 75    // High fluctuation threshold (e.g., 10 fluctuations)

// #define FLUCTUATION_COUNT_LOW 30       // Low fluctuation threshold (e.g., 3 fluctuations)
// #define FLUCTUATION_COUNT_MEDIUM 50       // Medium fluctuation threshold (e.g., 6 fluctuations)
// #define FLUCTUATION_COUNT_HIGH 75    // High fluctuation threshold (e.g., 10 fluctuations)

// int firstColumn = 9;   // Low intensity light (mild glow)
// int secondColumn = 8;  // Medium intensity light (flicker)
// int thirdColumn = 7;   // High intensity light (flash)

// float baselineLevel = 0.0; // Stores the baseline sound level

// // Function to calculate the baseline noise level
// float calculateBaseline(int duration)
// {
//   long startTime = millis();
//   long totalSound = 0;
//   int readings = 0;

//   while (millis() - startTime < duration)
//   {
//     totalSound += analogRead(SOUND_SENSOR_PIN);
//     readings++;
//     delay(10); // Small delay between readings
//   }

//   return (float)totalSound / readings; // Return average sound level
// }

// // Function to count fluctuations in the sound level within a window
// int countFluctuations(int duration, float threshold)
// {
//   long startTime = millis();
//   int fluctuationCount = 0;
//   float lastReading = analogRead(SOUND_SENSOR_PIN);

//   while (millis() - startTime < duration)
//   {
//     float currentReading = analogRead(SOUND_SENSOR_PIN);
//     if (abs(currentReading - lastReading) > threshold) // Check for a significant change
//     {
//       fluctuationCount++;
//     }
//     lastReading = currentReading;
//     delay(10); // Small delay between readings
//   }

//   return fluctuationCount;
// }

// void columnOne(int value) // Low intensity light
// {
//   if (value == 0)
//     digitalWrite(firstColumn, LOW);

//   else
//     digitalWrite(firstColumn, HIGH);
// }

// void columnTwo(int value) // Medium intensity light
// {
//   if (value == 0)
//     digitalWrite(secondColumn, LOW);
//   else
//     digitalWrite(secondColumn, HIGH);
// }

// void columnThree(int value) // High intensity light
// {
//   if (value == 0)
//     digitalWrite(thirdColumn, LOW);
//   else
//     digitalWrite(thirdColumn, HIGH);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);

//   Serial.begin(9600); // Initialize serial communication
//   pinMode(SOUND_SENSOR_PIN, INPUT);

//   Serial.println("Initializing... Measuring background noise levels...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline

//   Serial.print("Baseline Level Established: ");
//   Serial.println(baselineLevel);
//   Serial.println("Monitoring sound level changes...");
// }

// void loop()
// {
//   // Count fluctuations in sound level within the defined time window
//   int fluctuationCount = countFluctuations(FLUCTUATION_WINDOW, CHANGE_THRESHOLD);

//   // Monitor if the fluctuation count indicates significant noise
//   Serial.print("Fluctuations in the last ");
//   Serial.print(FLUCTUATION_WINDOW / 1000);
//   Serial.print(" second(s): ");
//   Serial.println(fluctuationCount);

//   // Adjust lighting based on fluctuation count
//   if (fluctuationCount >= FLUCTUATION_COUNT_HIGH)
//   {
//     // High noise: Flash the third column (maximum light)
//     columnThree(1);
//     columnTwo(0);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_MEDIUM)
//   {
//     // Medium noise: Flicker the second column (medium light)
//     columnThree(0);
//     columnTwo(1);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_LOW)
//   {
//     // Low noise: Low glow on the first column (mild light)
//     columnThree(0);
//     columnTwo(0);
//     columnOne(1);
//   }
//   else
//   {
//     // No significant fluctuations: Turn off lights
//     columnOne(0);
//     columnTwo(0);
//     columnThree(0);
//   }

//   delay(250);  // Small delay for better stability
// }







// #include <Arduino.h>

// #define SOUND_SENSOR_PIN_ZERO A0              // Analog Output pin for KY-037
// #define SOUND_SENSOR_PIN_ONE A1              // Analog Output pin for KY-037
// #define BASELINE_MEASURE_DURATION 5000   // Duration to measure baseline (in ms)
// #define CHANGE_THRESHOLD 1.9        // Increased threshold for detecting a fluctuation
// #define FLUCTUATION_WINDOW 2000          // Duration for counting fluctuations (in ms)
// // #define FLUCTUATION_COUNT_LOW 30       // Low fluctuation threshold (e.g., 3 fluctuations)
// // #define FLUCTUATION_COUNT_MEDIUM 50       // Medium fluctuation threshold (e.g., 6 fluctuations)
// // #define FLUCTUATION_COUNT_HIGH 75    // High fluctuation threshold (e.g., 10 fluctuations)

// #define FLUCTUATION_COUNT_LOW 25.0      // Low fluctuation threshold (e.g., 3 fluctuations)
// #define FLUCTUATION_COUNT_MEDIUM 50.0     // Medium fluctuation threshold (e.g., 6 fluctuations)
// #define FLUCTUATION_COUNT_HIGH 75.0     // High fluctuation threshold (e.g., 10 fluctuations)

// int firstColumn = 9;   // Low intensity light (mild glow)
// int secondColumn = 6;  // Medium intensity light (flicker)
// int thirdColumn = 5;   // High intensity light (flash)

// float baselineLevel = 0.0; // Stores the baseline sound level

// // Function to calculate the baseline noise level
// float calculateBaseline(int duration)
// {
//   long startTime = millis();
//   long totalSoundZero = 0;
//   long totalSoundOne = 0;
//   int readings = 0;

//   while (millis() - startTime < duration)
//   {
//     totalSoundZero += analogRead(SOUND_SENSOR_PIN_ZERO);
//     totalSoundOne += analogRead(SOUND_SENSOR_PIN_ONE);
//     readings++;
//     delay(10); // Small delay between readings
//   }
//   float result = (((float)totalSoundZero / readings) + ((float)totalSoundOne / readings))/2;
//   return result; // Return average sound level
// }

// // Function to count fluctuations in the sound level within a window
// int countFluctuations(int duration, float threshold)
// {
//   long startTime = millis();
//   int fluctuationCount = 0;
//   float lastReading = (analogRead(SOUND_SENSOR_PIN_ZERO) + analogRead(SOUND_SENSOR_PIN_ONE))/2;

//   while (millis() - startTime < duration)
//   {
//     float currentReading = (analogRead(SOUND_SENSOR_PIN_ZERO) + analogRead(SOUND_SENSOR_PIN_ONE))/2;
//     if (abs(currentReading - lastReading) > threshold) // Check for a significant change
//       fluctuationCount++;
//     lastReading = currentReading;
//     delay(10); // Small delay between readings
//   }

//   return fluctuationCount;
// }

// void columnOne(int value) // Low intensity light
// {
//   if (value == 0)
//     analogWrite(firstColumn, 0);

//   else
//     analogWrite(firstColumn, 220);
// }

// void columnTwo(int value) // Medium intensity light
// {
//   if (value == 0)
//     analogWrite(secondColumn, 0);
//   else
//     analogWrite(secondColumn, 220);
// }

// void columnThree(int value) // High intensity light
// {
//   if (value == 0)
//     analogWrite(thirdColumn, 0);
//   else
//     analogWrite(thirdColumn, 220);
// }

// void setup()
// {
//   pinMode(firstColumn, OUTPUT);
//   pinMode(secondColumn, OUTPUT);
//   pinMode(thirdColumn, OUTPUT);
//   columnOne(0);
//   columnTwo(0);
//   columnThree(0);

//   Serial.begin(9600); // Initialize serial communication
//   pinMode(SOUND_SENSOR_PIN_ZERO, INPUT);
//   pinMode(SOUND_SENSOR_PIN_ONE, INPUT);

//   Serial.println("Initializing... Measuring background noise levels...");
//   baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline

//   Serial.print("Baseline Level Established: ");
//   Serial.println(baselineLevel);
//   Serial.println("Monitoring sound level changes...");
// }

// void loop()
// {
//   // Count fluctuations in sound level within the defined time window
//   int fluctuationCount = countFluctuations(FLUCTUATION_WINDOW, CHANGE_THRESHOLD);

//   // Monitor if the fluctuation count indicates significant noise
//   Serial.print("Fluctuations in the last ");
//   Serial.print(FLUCTUATION_WINDOW / 1000);
//   Serial.print(" second(s): ");
//   Serial.println(fluctuationCount);

//   // Adjust lighting based on fluctuation count
//   if (fluctuationCount >= FLUCTUATION_COUNT_HIGH)
//   {
//     // High noise: Flash the third column (maximum light)
//     columnThree(1);
//     columnTwo(0);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_MEDIUM)
//   {
//     // Medium noise: Flicker the second column (medium light)
//     columnThree(0);
//     columnTwo(1);
//     columnOne(0);
//   }
//   else if (fluctuationCount >= FLUCTUATION_COUNT_LOW)
//   {
//     // Low noise: Low glow on the first column (mild light)
//     columnThree(0);
//     columnTwo(0);
//     columnOne(1);
//   }
//   else
//   {
//     // No significant fluctuations: Turn off lights
//     columnOne(0);
//     columnTwo(0);
//     columnThree(0);
//   }

//   delay(250);  // Small delay for better stability
// }















#include <Arduino.h>

#define SOUND_SENSOR_PIN_ZERO A0              // Analog Output pin for KY-037
#define SOUND_SENSOR_PIN_ONE A1              // Analog Output pin for KY-037
#define BASELINE_MEASURE_DURATION 5000       // Duration to measure baseline (in ms)
#define CHANGE_THRESHOLD 1.9                 // Increased threshold for detecting a fluctuation
#define FLUCTUATION_WINDOW 2000              // Duration for counting fluctuations (in ms)

#define FLUCTUATION_COUNT_LOW 40         // Low fluctuation threshold (e.g., 3 fluctuations)
#define FLUCTUATION_COUNT_MEDIUM 70     // Medium fluctuation threshold (e.g., 6 fluctuations)
#define FLUCTUATION_COUNT_HIGH 90         // High fluctuation threshold (e.g., 10 fluctuations)

int firstColumn = 9;   // Low intensity light (mild glow)
int secondColumn = 6;  // Medium intensity light (flicker)
int thirdColumn = 5;   // High intensity light (flash)

float baselineLevel = 0.0; // Stores the baseline sound level

// Function to calculate the baseline noise level
float calculateBaseline(int duration)
{
  unsigned long startTime = millis();
  long totalSoundZero = 0;
  long totalSoundOne = 0;
  int readings = 0;

  while (millis() - startTime < (unsigned long)duration)
  {
    totalSoundZero += analogRead(SOUND_SENSOR_PIN_ZERO);
    totalSoundOne += analogRead(SOUND_SENSOR_PIN_ONE);
    readings++;
    delay(10); // Small delay between readings
  }
  float result = (((float)totalSoundZero / readings) + ((float)totalSoundOne / readings)) / 2;
  return result; // Return average sound level
}

// Function to count fluctuations in the sound level within a window
int countFluctuations(int duration, float threshold)
{
  unsigned long startTime = millis();
  int fluctuationCount = 0;
  float lastReading = (analogRead(SOUND_SENSOR_PIN_ZERO) + analogRead(SOUND_SENSOR_PIN_ONE)) / 2;

  while (millis() - startTime < (unsigned long)duration)
  {
    float currentReading = (analogRead(SOUND_SENSOR_PIN_ZERO) + analogRead(SOUND_SENSOR_PIN_ONE)) / 2;
    if (abs(currentReading - lastReading) > threshold) // Check for a significant change
      fluctuationCount++;
    lastReading = currentReading;
    delay(10); // Small delay between readings
  }

  return fluctuationCount;
}

void columnOne(int value) // Low intensity light
{
  if (value == 0)
    analogWrite(firstColumn, 0);
  else
    analogWrite(firstColumn, 220);
}

void columnTwo(int value) // Medium intensity light
{
  if (value == 0)
    analogWrite(secondColumn, 0);
  else
    analogWrite(secondColumn, 220);
}

void columnThree(int value) // High intensity light
{
  if (value == 0)
    analogWrite(thirdColumn, 0);
  else
    analogWrite(thirdColumn, 220);
}

void setup()
{
  pinMode(firstColumn, OUTPUT);
  pinMode(secondColumn, OUTPUT);
  pinMode(thirdColumn, OUTPUT);
  columnOne(0);
  columnTwo(0);
  columnThree(0);

  Serial.begin(9600); // Initialize serial communication
  pinMode(SOUND_SENSOR_PIN_ZERO, INPUT);
  pinMode(SOUND_SENSOR_PIN_ONE, INPUT);

  Serial.println("Initializing... Measuring background noise levels...");
  baselineLevel = calculateBaseline(BASELINE_MEASURE_DURATION); // Measure baseline

  Serial.print("Baseline Level Established: ");
  Serial.println(baselineLevel);
  Serial.println("Monitoring sound level changes...");
}

void loop()
{
  // Count fluctuations in sound level within the defined time window
  int fluctuationCount = countFluctuations(FLUCTUATION_WINDOW, CHANGE_THRESHOLD);

  // Monitor if the fluctuation count indicates significant noise
  Serial.print("Fluctuations in the last ");
  Serial.print(FLUCTUATION_WINDOW / 1000);
  Serial.print(" second(s): ");
  Serial.println(fluctuationCount);
  
  // Adjust lighting based on fluctuation count
  if (fluctuationCount >= FLUCTUATION_COUNT_HIGH)
  {
    // High noise: Flash the third column (maximum light)
    columnThree(1);
    columnTwo(1);
    columnOne(1);
  }
  else if (fluctuationCount >= FLUCTUATION_COUNT_MEDIUM)
  {
    // Medium noise: Flicker the second column (medium light)
    columnThree(0);
    columnTwo(1);
    columnOne(1);
  }
  else if (fluctuationCount >= FLUCTUATION_COUNT_LOW)
  {
    // Low noise: Low glow on the first column (mild light)
    columnThree(0);
    columnTwo(0);
    columnOne(1);
  }
  else
  {
    // No significant fluctuations: Turn off lights
    columnOne(0);
    columnTwo(0);
    columnThree(0);
  }

  delay(250);  // Small delay for better stability
}

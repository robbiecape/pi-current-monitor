/**
 * ESP32 Current Monitor
 *
 * Measures AC current using CT sensor and publishes to MQTT
 * Uses ESP32 Sensor Framework for WiFi, MQTT, and data buffering
 */

#include "framework/ESPSensorCore.h"

// ============================================================================
// SENSOR CONFIGURATION
// ============================================================================

// Current Sensor Setup
#define CT_PIN 34           // GPIO34 (ADC1_CH6) - connected to CT sensor
#define SAMPLES 2000        // Number of samples to read for RMS calculation
#define SAMPLE_RATE 4000    // Target samples per second (adjust based on testing)
#define ADC_BITS 4096       // 12-bit ADC (0-4095)
#define ADC_VOLTAGE 3.3     // ESP32 ADC reference voltage
#define CT_RATIO 35.2       // CT ratio calibrated for this circuit (see README)

// Calibration constant
float currentCalibration = (CT_RATIO * ADC_VOLTAGE) / ADC_BITS;  // Amps per ADC count

// Framework instance
ESPSensorCore framework;

// ===== CURRENT SENSING FUNCTIONS =====

float readCurrentRMS() {
  /**
   * Read AC current using RMS calculation - DEBUG VERSION
   */
  
  unsigned long sum = 0;
  unsigned long sumRaw = 0;  // Track raw ADC values
  int minADC = 4095;
  int maxADC = 0;
  int samples = 0;
  
  // Sample the waveform rapidly
  unsigned long startTime = micros();
  
  for (int i = 0; i < SAMPLES; i++) {
    int rawADC = analogRead(CT_PIN);  // Read ADC (0-4095)
    
    // Track min/max for debugging
    if (rawADC < minADC) minADC = rawADC;
    if (rawADC > maxADC) maxADC = rawADC;
    sumRaw += rawADC;
    
    // Convert to voltage and remove DC bias
    float voltage = (rawADC * ADC_VOLTAGE / ADC_BITS) - 1.65;
    
    // Square the value and add to sum
    sum += (voltage * voltage * 1000000);  // Multiply by 1M to avoid float precision issues
    samples++;
  }
  
  unsigned long endTime = micros();
  float sampleTime = (endTime - startTime) / 1000.0;  // milliseconds
  float actualSampleRate = (samples / sampleTime) * 1000.0;  // samples per second
  
  // Calculate averages and ranges
  float avgRawADC = (float)sumRaw / samples;
  float avgVoltage = avgRawADC * ADC_VOLTAGE / ADC_BITS;
  
  // Calculate RMS voltage
  float meanSquare = (float)sum / samples / 1000000.0;  // Divide out our scaling factor
  float rmsVoltage = sqrt(meanSquare);
  
  // Convert RMS voltage to RMS current using CT calibration
  float rmsCurrent = rmsVoltage * CT_RATIO;
  
  // Debug output - EXPANDED
  Serial.printf("RAW ADC: avg=%.1f min=%d max=%d (expected avg~2048)\n", avgRawADC, minADC, maxADC);
  Serial.printf("Avg Voltage: %.3fV (expected ~1.65V)\n", avgVoltage);
  Serial.printf("Samples: %d, Time: %.2fms, Rate: %.0f Hz, RMS Voltage: %.4fV, Current: %.2fA\n", 
                samples, sampleTime, actualSampleRate, rmsVoltage, rmsCurrent);
  Serial.println();
  
  return rmsCurrent;
}

float testADCBias() {
  /**
   * Test function to check ADC bias voltage
   * Should read around 2048 (middle of 0-4095) when no current flowing
   * Call this during setup to verify circuit is working
   */
  long sum = 0;
  int samples = 100;
  
  for (int i = 0; i < samples; i++) {
    sum += analogRead(CT_PIN);
    delay(10);
  }
  
  float avgADC = (float)sum / samples;
  float avgVoltage = (avgADC * ADC_VOLTAGE) / ADC_BITS;
  
  Serial.printf("ADC Bias Test - Average ADC: %.1f (expected ~2048), Voltage: %.3fV (expected ~1.65V)\n", 
                avgADC, avgVoltage);
  
  return avgVoltage;
}

// ===== END CURRENT SENSING FUNCTIONS =====

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // Configure ADC for current sensing
  analogReadResolution(12);  // 12-bit resolution (0-4095)
  analogSetAttenuation(ADC_11db);  // Full 0-3.3V range

  // Test ADC bias (verify circuit is working)
  Serial.println("\n===== Testing ADC Bias =====");
  testADCBias();
  Serial.println("============================\n");

  // Initialize framework (handles WiFi, MQTT, buffering, web server)
  framework.begin();

  Serial.println("Current monitor ready - GPIO34");
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
  // Update framework (handles WiFi, MQTT, LED, web server, buffering)
  framework.update();

  // Check if it's time to publish sensor data
  if (framework.shouldPublish()) {
    // Read current sensor
    float currentAmps = readCurrentRMS();

    // Publish to MQTT (or buffer if disconnected)
    framework.publish("current_amps", currentAmps);
  }
}
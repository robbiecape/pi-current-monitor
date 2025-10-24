================================================================================
ESP32 CURRENT MONITORING SYSTEM - README
================================================================================

PROJECT OVERVIEW
--------------------------------------------------------------------------------
Non-invasive AC current monitoring using ESP32 and SCT013 current transformers,
with MQTT data publishing. Designed for marine/boat environments.

Key Features:
  * Non-invasive measurement (no wire cutting required)
  * Real-time current monitoring with RMS calculation
  * MQTT publishing every 5 seconds
  * NTP time synchronization
  * Automatic WiFi configuration portal
  * Support for multiple CT sensors (expandable to 4+ circuits)


HARDWARE REQUIRED
--------------------------------------------------------------------------------
Core Components:
  * ESP32 Development Board (ESP32-WROOM-32 or similar)
  * SCT013-050 CT Sensor (50A/1V voltage output) - or SCT013-000V (100A/1V)
  * 2x 10kΩ resistors (±5% tolerance acceptable)
  * 1x 10µF electrolytic capacitor (25V rating)
  * 3.5mm Audio Jack - PCB mount (optional, e.g., Tegg PJ-307)
  * Breadboard (for prototyping)
  * Perfboard (5x7cm, for permanent build)
  * Waterproof Enclosure (IP65+ rated with cable glands)
  * USB Cable (for power and programming)

Optional:
  * Additional CT Sensors (for monitoring multiple circuits)
  * Desiccant Pack (moisture control in enclosure)
  * Conformal Coating (PCB protection in marine environment)

Estimated Cost: ~$40-55 per channel


CIRCUIT DESIGN - QUICK REFERENCE
--------------------------------------------------------------------------------
For detailed wiring diagrams, component placement, and troubleshooting,
see WIRING.pdf

Basic Circuit:
  ESP32 3.3V ──┬── 10kΩ R1 ──┬── ESP32 GPIO34 (ADC)
               │              │
                              ├── 10µF Cap (+) ──┬── CT White Wire
                              │                  │
                              └── 10kΩ R2 ────┬──┴── CT Red Wire
                                              │
  ESP32 GND ──────────────────────────────────┘

How It Works:
  1. Voltage Divider (R1 + R2): Creates 1.65V DC bias at ADC input
  2. AC Coupling Capacitor: Blocks DC, passes AC signal from CT
  3. CT Sensor: Outputs 0-1V AC proportional to current (50A = 1V)
  4. ESP32 ADC: Samples at ~24kHz and calculates RMS current

Critical Notes:
  * CT wires are interchangeable (red/white can be swapped)
  * Shield wire (if present) is NOT needed
  * GPIO34 recommended for ADC (or use 32, 33, 35, 36, 39)
  * DO NOT connect CT in parallel with voltage divider
  * MUST use capacitor to AC-couple the signal


PIN CONNECTIONS
--------------------------------------------------------------------------------
Component          ESP32 Pin       Breadboard Row
---------          ---------       --------------
Power              3.3V            Row 10
Ground             GND             Row 25
ADC Input          GPIO34          Row 15
R1 (10kΩ)          3.3V → GPIO34   Row 10-15
R2 (10kΩ)          GPIO34 → GND    Row 15-25
Capacitor (+)      GPIO34 side     Row 15
Capacitor (-)      CT signal side  Row 20
CT Red Wire        GND             Row 25
CT White Wire      Through cap     Row 20


SOFTWARE SETUP
--------------------------------------------------------------------------------
Arduino IDE Configuration:

1. Install ESP32 Board Support:
   - File → Preferences → Additional Board Manager URLs
   - Add: https://dl.espressif.com/dl/package_esp32_index.json
   - Tools → Board → Boards Manager → Search "ESP32" → Install

2. Install Required Libraries:
   - WiFiManager (by tzapu) - v2.0.17
   - PubSubClient (by Nick O'Leary) - v2.8
   - ESPmDNS (included with ESP32)
   - Preferences (included with ESP32)

3. Board Settings:
   - Board: "ESP32 Dev Module"
   - Upload Speed: 921600
   - CPU Frequency: 240MHz
   - Flash Frequency: 80MHz
   - Flash Mode: QIO
   - Flash Size: 4MB
   - Partition Scheme: Default


INITIAL CONFIGURATION
--------------------------------------------------------------------------------
On first boot, the ESP32 creates a WiFi access point:
  * SSID: "ESP32-CurrentMonitor"
  * Connect with phone/computer
  * Web portal opens automatically (or go to 192.168.4.1)
  * Enter WiFi credentials and MQTT broker IP
  * Save - ESP32 reboots and connects

To reset settings:
  * Hold BOOT button for 3+ seconds during power-up


CALIBRATION - REQUIRED FOR ACCURACY
--------------------------------------------------------------------------------
The CT_RATIO constant must be calibrated using a known load:

1. Connect a known load (use Kill-A-Watt or clamp meter)
2. Compare ESP32 reading to actual current
3. Calculate new CT_RATIO:

   Calibration_Factor = ESP32_Reading ÷ Actual_Current
   New_CT_RATIO = Current_CT_RATIO ÷ Calibration_Factor

Example from this build:
  * Kill-A-Watt showed: 8.24A
  * ESP32 showed: 23.4A
  * Original CT_RATIO: 100.0
  * Calibration Factor: 23.4 ÷ 8.24 = 2.84
  * New CT_RATIO: 100 ÷ 2.84 = 35.2

Update in code:
  #define CT_RATIO 35.2  // Calibrated value

Note: This calibration is specific to this circuit design and component
values. If you use identical parts, the same calibration should work for
all units. Different resistor values or CT models require recalibration.


MQTT TOPICS
--------------------------------------------------------------------------------
Data published to:
  gooddecisions/{MAC_ADDRESS}/current    - Current in Amps (float)
  gooddecisions/{MAC_ADDRESS}/timestamp  - ISO 8601 or BOOT+seconds
  gooddecisions/{MAC_ADDRESS}/version    - Firmware version (retained)

Example:
  gooddecisions/441D64F83968/current → "8.24"
  gooddecisions/441D64F83968/timestamp → "2025-10-23T00:46:32Z"
  gooddecisions/441D64F83968/version → "v1.0 Oct 23 2025 17:15:42"


OPERATION
--------------------------------------------------------------------------------
LED Behavior:
  * Boot: Solid ON
  * Normal: Quick blink every 30 seconds (heartbeat)
  * Connection issues: Fast blink (2Hz) or slow blink (every 30s)

Serial Monitor (115200 baud):
  RAW ADC: avg=1835 min=1500 max=2160
  Avg Voltage: 1.48V
  Samples: 2000, Rate: 24000 Hz, RMS Voltage: 0.234V, Current: 8.24A
  Published - Current: 8.24A at 2025-10-23T00:46:32Z

Measurement Accuracy:
  * Optimal Range: 5-50A (for 50A CT) - accuracy ±5%
  * Acceptable Range: 3-50A - reasonable accuracy
  * Poor Accuracy: Below 3A - noise dominates, unreliable
  * Maximum: Do not exceed CT rating (50A)

Why Low Currents Are Inaccurate:
  CT sensors are optimized for their rated range. Below 10% of rating
  (~5A for 50A CT), the signal is too small compared to ADC noise floor.


TROUBLESHOOTING
--------------------------------------------------------------------------------
Problem: Readings stuck at ~146A or ADC at 4095
  Cause: CT connected incorrectly (parallel with voltage divider)
  Solution: CT must connect THROUGH capacitor, not directly to divider
  See WIRING.pdf for correct circuit

Problem: Readings show ~17A with no load
  Cause: Normal ADC noise floor - expected behavior
  Solution: No action needed. Disappears when measuring loads >5A

Problem: Brownout detector / constant reboots
  Cause: Insufficient USB power
  Solution: Use 2A+ USB adapter, powered hub, or better cable

Problem: WiFi won't connect
  Cause: Wrong credentials or out of range
  Solution: Reset (hold BOOT 3 sec), move closer to router

Problem: MQTT connection fails (rc=-2)
  Cause: Mosquitto not listening on network
  Solution: Edit /opt/homebrew/etc/mosquitto/mosquitto.conf
    Add: listener 1883 0.0.0.0
    Add: allow_anonymous true
    Restart: brew services restart mosquitto


MARINE/BOAT INSTALLATION
--------------------------------------------------------------------------------
Enclosure Requirements:
  * Rating: IP65 minimum (waterproof when closed)
  * Material: Nylon or ABS plastic (corrosion resistant)
  * Cable Glands: PG7 or PG9 size for CT cables

Environmental Protection:
  1. Apply conformal coating to perfboard after soldering
  2. Place desiccant pack inside enclosure
  3. Consider Gore-Tex breather vent for pressure equalization
  4. Use marine-grade cable glands with O-rings

Installation Location:
  * Dry location preferred (avoid bilge)
  * Accessible for troubleshooting
  * Near power source (USB or 12V→5V converter)
  * Good WiFi coverage
  * Away from direct sunlight

Mounting:
  * Use stainless steel fasteners
  * Secure perfboard with standoffs
  * Strain relief on all cables
  * Consider vibration isolation


EXPANDING THE SYSTEM
--------------------------------------------------------------------------------
Adding More CT Sensors:

Available ADC pins: GPIO32, 33, 35, 36, 39

For each additional CT:
  1. Replicate circuit (voltage divider + capacitor + CT)
  2. Use different GPIO pin
  3. Update code to read multiple pins
  4. Publish to separate MQTT topics:
     gooddecisions/{MAC}/current1
     gooddecisions/{MAC}/current2
     gooddecisions/{MAC}/current3

Power Consumption:
  * Active (WiFi, sampling): ~80-120mA @ 5V (0.4-0.6W)
  * 24/7 operation: ~1-2W continuous


TECHNICAL SPECIFICATIONS
--------------------------------------------------------------------------------
Parameter              Value
---------              -----
Supply Voltage         5V USB (3.3V internally regulated)
ADC Resolution         12-bit (0-4095)
ADC Input Range        0-3.3V
Sample Rate            ~24,000 samples/second
Samples per Reading    2000 (for accurate RMS)
Publish Interval       5 seconds
CT Sensor Range        0-50A AC (or 0-100A for other models)
Measurement Accuracy   ±5% @ 5-50A range
WiFi                   802.11 b/g/n 2.4GHz
MQTT                   QoS 0, unencrypted


SAFETY WARNINGS
--------------------------------------------------------------------------------
⚠ ELECTRICAL SAFETY:
  * CT sensors provide galvanic isolation
  * High voltage wire never touches ESP32
  * Turn off circuit power before clamping CT
  * Do not exceed CT's rated current (50A or 100A)
  * Verify capacitor polarity (incorrect = failure/heat)

⚠ MARINE ENVIRONMENT:
  * Use IP-rated enclosure
  * Follow marine electrical standards (ABYC in USA)
  * Fuse/breaker on power supply
  * Regular inspection for corrosion


FUTURE ENHANCEMENTS
--------------------------------------------------------------------------------
Possible improvements:
  [ ] Deep sleep mode (battery operation)
  [ ] Local SD card logging
  [ ] Web dashboard (serve from ESP32)
  [ ] OTA firmware updates
  [ ] Multiple simultaneous CT sensors
  [ ] Power factor measurement (requires voltage sensing)
  [ ] Energy integration (kWh calculation)
  [ ] Configurable publish intervals
  [ ] MQTT authentication (TLS/SSL)


FILES IN THIS PROJECT
--------------------------------------------------------------------------------
README.txt                    - This file (overview and quick reference)
WIRING.pdf                    - Detailed circuit diagrams and layouts
ESP32_CurrentSensor.ino       - Arduino sketch (main code)


TESTING NOTES
--------------------------------------------------------------------------------
This circuit has been tested and validated:
  * Kill-A-Watt meter used for calibration (8.24A reference)
  * Multimeter verified voltage divider (1.48V bias)
  * Two CT sensors tested - both work with same calibration
  * Shield/ground wire confirmed unnecessary
  * 3.5mm jack/socket approach validated
  * Tested with loads from 1A to 50A


VERSION HISTORY
--------------------------------------------------------------------------------
v1.0 - October 23, 2025
  * Initial release
  * Single CT sensor support
  * WiFiManager configuration
  * MQTT publishing
  * NTP time sync
  * Calibrated for 50A CT (SCT013-050)

  
CREDITS
--------------------------------------------------------------------------------
Hardware: ESP32 by Espressif, SCT013 by YHDC
Software: Arduino ESP32 Core, WiFiManager, PubSubClient
Design assistance: Claude (Anthropic AI)

Author: Robbie Cape
Date: October 23, 2025

================================================================================
END OF README
================================================================================
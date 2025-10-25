# ESP32 3-Channel Current Monitor - Production Perfboard Layout

## Board Specifications

**Board size:** 30 columns x 22 rows
**Physical:** 76mm x 56mm (7.6cm x 5.6cm)
**Perfboard type:** Standard 2.54mm isolated holes

**Components:**
- 1x ESP32-WROOM-32 DevKit (15 pins/row, 11 holes between rows)
- 3x CT sensor channels (GPIO34, GPIO35, GPIO36)
- 6x 10kΩ resistors (1/4W)
- 3x 10µF electrolytic capacitors (25V)
- 3x 3.5mm PCB mount stereo jacks
- Wire for power distribution

---

## Complete Board Layout - Top View

```
Col:  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
    ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
R1  │3V│══│══│══│══│══│══│══│══│══│══│══│══│══│3V│  │  │  │  │  │  │  │  │  │  │  │  │  │  │GN│ Power Rails
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R2  │GN│══│══│══│══│══│══│══│══│══│══│══│══│══│GN│  │  │  │  │  │  │  │  │  │  │  │  │  │  │GN│
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R3  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R4  │  │【 ESP32 Socket Header Row 1 - 15 pins    】│  │R1│●│R2│  │  │  │  │  │  │  │  │  │  │ CH1 Resistors
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R5  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │+ │  │  │  │  │  │  │  │  │  │  │  │ CH1 Cap+
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R6  │  │3V│  │  │  │  │  │34│  │  │  │  │  │GN│  │  │  │  │- │  │  │  │  │  │  │  │  │  │  │  │ CH1 Cap- / ESP32 pins
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R7  │  │  │                                       │  │  │  │【Jack1】│  │  │  │  │  │  │  │  │ CH1 3.5mm Jack
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R8  │  │  │    [ESP32 - USB port faces right →]  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R9  │  │  │                                       │  │R1│●│R2│  │  │  │  │  │  │  │  │  │  │  │ CH2 Resistors
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R10 │  │  │                                       │  │  │  │+ │  │  │  │  │  │  │  │  │  │  │  │ CH2 Cap+
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R11 │  │  │                                       │  │  │  │- │  │  │  │  │  │  │  │  │  │  │  │ CH2 Cap-
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R12 │  │  │                                       │  │  │  │【Jack2】│  │  │  │  │  │  │  │  │ CH2 3.5mm Jack
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R13 │  │  │                                       │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R14 │  │  │                                       │  │R1│●│R2│  │  │  │  │  │  │  │  │  │  │  │ CH3 Resistors
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R15 │  │【 ESP32 Socket Header Row 2 - 15 pins    】│  │  │  │+ │  │  │  │  │  │  │  │  │  │  │ CH3 Cap+
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R16 │  │  │  │  │  │  │  │35│  │  │  │36│  │  │  │  │  │  │- │  │  │  │  │  │  │  │  │  │  │  │ CH3 Cap- / GPIO35,36
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R17 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │【Jack3】│  │  │  │  │  │  │  │  │ CH3 3.5mm Jack
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R18 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R19 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R20 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R21 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
R22 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

Legend:
  3V = 3.3V power rail        GN = GND power rail
  34, 35, 36 = GPIO pins      ● = Junction point
  R1, R2 = 10kΩ resistors     + = Cap positive    - = Cap negative
  【Jack】= 3.5mm PCB jack
```

---

## Detailed Component Positions

### Power Rails (Rows 1-2)

**Row 1: 3.3V Power Rail**
- Columns 1-15: Wire connecting all points
- Column 15: Taps to ESP32 3.3V pin
- Column 30: Optional test point

**Row 2: GND Power Rail**
- Columns 1-15: Wire connecting all points
- Column 15: Taps to ESP32 GND pin
- Column 30: Optional test point

### ESP32 Socket (Rows 4-15, Columns 2-16)

**Header Row 1:** Row 4, Columns 2-16 (15 pins)
**Header Row 2:** Row 15, Columns 2-16 (15 pins)

**Critical pins to identify on YOUR ESP32:**
- **3.3V pin** (estimated Row 6, Column 2)
- **GPIO34 pin** (estimated Row 6, Column 8)
- **GPIO35 pin** (estimated Row 16, Column 8)
- **GPIO36 pin** (estimated Row 16, Column 12)
- **GND pin** (estimated Row 6, Column 14)

⚠️ **You MUST verify these positions** - ESP32 pin layouts vary by manufacturer!

### Channel 1 - CT Sensor 1 (GPIO34)

**Location:** Rows 4-7, Columns 17-22

**R1 (10kΩ):**
- Leg 1: Row 4, Column 17
- Leg 2: Row 4, Column 18 (junction)

**R2 (10kΩ):**
- Leg 1: Row 4, Column 18 (junction - same as R1 leg 2)
- Leg 2: Row 4, Column 19

**Capacitor (10µF):**
- Positive (+): Row 5, Column 19
- Negative (-): Row 6, Column 19

**3.5mm Jack:**
- Mount: Rows 6-7, Columns 19-22
- Tip (signal): Row 6, Column 19 (connects to cap negative)
- Sleeve (GND): Row 7, Column 19

### Channel 2 - CT Sensor 2 (GPIO35)

**Location:** Rows 9-12, Columns 17-22

**R1 (10kΩ):**
- Leg 1: Row 9, Column 17
- Leg 2: Row 9, Column 18 (junction)

**R2 (10kΩ):**
- Leg 1: Row 9, Column 18 (junction)
- Leg 2: Row 9, Column 19

**Capacitor (10µF):**
- Positive (+): Row 10, Column 19
- Negative (-): Row 11, Column 19

**3.5mm Jack:**
- Mount: Rows 11-12, Columns 19-22
- Tip (signal): Row 11, Column 19 (connects to cap negative)
- Sleeve (GND): Row 12, Column 19

### Channel 3 - CT Sensor 3 (GPIO36)

**Location:** Rows 14-17, Columns 17-22

**R1 (10kΩ):**
- Leg 1: Row 14, Column 17
- Leg 2: Row 14, Column 18 (junction)

**R2 (10kΩ):**
- Leg 1: Row 14, Column 18 (junction)
- Leg 2: Row 14, Column 19

**Capacitor (10µF):**
- Positive (+): Row 15, Column 19
- Negative (-): Row 16, Column 19

**3.5mm Jack:**
- Mount: Rows 16-17, Columns 19-22
- Tip (signal): Row 16, Column 19 (connects to cap negative)
- Sleeve (GND): Row 17, Column 19

---

## Wiring List (All on Bottom Side)

### Power Distribution (create these "rails" with wire)

1. **3.3V Rail:** Row 1, Columns 1→15 (horizontal wire)
2. **GND Rail:** Row 2, Columns 1→30 (horizontal wire)

### Channel 1 Wiring

3. **R1 top to 3.3V:** Row 4, Col 17 → Row 1, Col 17
4. **R2 bottom to GND:** Row 4, Col 19 → Row 2, Col 19
5. **Junction to GPIO34:** Row 4, Col 18 → Row 6, Col 8 (ESP32 GPIO34 pin)
6. **Junction to Cap+:** Row 4, Col 18 → Row 5, Col 19
7. **Jack sleeve to GND:** Row 7, Col 19 → Row 2, Col 19

### Channel 2 Wiring

8. **R1 top to 3.3V:** Row 9, Col 17 → Row 1, Col 17
9. **R2 bottom to GND:** Row 9, Col 19 → Row 2, Col 19
10. **Junction to GPIO35:** Row 9, Col 18 → Row 16, Col 8 (ESP32 GPIO35 pin)
11. **Junction to Cap+:** Row 9, Col 18 → Row 10, Col 19
12. **Jack sleeve to GND:** Row 12, Col 19 → Row 2, Col 19

### Channel 3 Wiring

13. **R1 top to 3.3V:** Row 14, Col 17 → Row 1, Col 17
14. **R2 bottom to GND:** Row 14, Col 19 → Row 2, Col 19
15. **Junction to GPIO36:** Row 14, Col 18 → Row 16, Col 12 (ESP32 GPIO36 pin)
16. **Junction to Cap+:** Row 14, Col 18 → Row 15, Col 19
17. **Jack sleeve to GND:** Row 17, Col 19 → Row 2, Col 19

### ESP32 Power

18. **ESP32 3.3V to rail:** Row 6, Col 2 → Row 1, Col 2
19. **ESP32 GND to rail:** Row 6, Col 14 → Row 2, Col 14

**Total: 19 wire connections on bottom side**

---

## Assembly Steps

### Stage 1: Install ESP32 Socket

1. **Break header strips:**
   - 2x 15-pin female header strips

2. **Position on perfboard:**
   - Row 4, Columns 2-16: First header
   - Row 15, Columns 2-16: Second header

3. **Alignment:**
   - Insert headers into board
   - Plug ESP32 into headers (ensures alignment)
   - Tape in place

4. **Solder:**
   - Flip board (ESP32 still plugged in)
   - Solder all 30 pins
   - Remove ESP32
   - Trim pins flush

5. **Identify GPIO pins:**
   - Using multimeter continuity mode
   - Find socket holes for: 3.3V, GPIO34, GPIO35, GPIO36, GND
   - **Mark with permanent marker!**

---

### Stage 2: Create Power Rails

1. **3.3V rail (Row 1):**
   - Cut ~15cm of 22AWG wire
   - Strip 1cm from each end
   - Solder horizontally along Row 1, Columns 1-15
   - Create "bus" by connecting holes with wire on bottom

2. **GND rail (Row 2):**
   - Cut ~20cm of 22AWG wire
   - Solder horizontally along Row 2, Columns 1-30
   - This will be the main ground reference

3. **Connect ESP32 to rails:**
   - Wire from ESP32 3.3V pin → 3.3V rail
   - Wire from ESP32 GND pin → GND rail

---

### Stage 3: Build Channel 1 (GPIO34)

**Resistors:**
1. Insert R1: Row 4, Col 17 to Col 18
2. Insert R2: Row 4, Col 18 to Col 19 (shares junction hole with R1)
3. Solder from bottom
4. Wire R1 top (Col 17) to 3.3V rail (Row 1)
5. Wire R2 bottom (Col 19) to GND rail (Row 2)

**Test voltage divider:**
- Power on ESP32
- Measure junction (Row 4, Col 18) to GND
- Should read 1.65V DC ✅

**Capacitor:**
1. Identify polarity (white stripe = negative)
2. Insert: Positive at Row 5 Col 19, Negative at Row 6 Col 19
3. Solder from bottom
4. Wire Cap+ to junction (Row 4, Col 18)

**3.5mm Jack:**
1. Position jack at Rows 6-7, Cols 19-22
2. Identify pins: Tip (signal), Ring (unused), Sleeve (GND)
3. Solder jack to board
4. Wire Tip to Cap negative (Row 6, Col 19)
5. Wire Sleeve to GND rail (Row 2)

**GPIO Connection:**
1. Wire from junction (Row 4, Col 18) to GPIO34 socket pin
2. Test continuity with multimeter

**Test Channel 1:**
- Plug CT sensor into Jack 1
- Upload code with GPIO34 enabled
- Verify readings

---

### Stage 4: Build Channel 2 (GPIO35)

Repeat Stage 3 steps using:
- Rows 9-12 instead of Rows 4-7
- GPIO35 instead of GPIO34
- Same column positions (17-22)

---

### Stage 5: Build Channel 3 (GPIO36)

Repeat Stage 3 steps using:
- Rows 14-17 instead of Rows 4-7
- GPIO36 instead of GPIO34
- Same column positions (17-22)

---

## Testing Checklist

### Per-Channel Tests (do for each channel)

**Visual Inspection:**
- [ ] Capacitor polarity correct (white stripe = negative)
- [ ] No solder bridges
- [ ] All joints shiny
- [ ] Jack firmly mounted

**Voltage Tests (power ON, no CT connected):**
- [ ] Junction reads 1.65V DC (±0.2V)
- [ ] GPIO pin reads 1.65V DC
- [ ] Cap positive reads 1.65V DC

**Continuity Tests (power OFF):**
- [ ] 3.3V rail → R1 top
- [ ] R1 bottom → R2 top (junction)
- [ ] R2 bottom → GND rail
- [ ] Junction → GPIO pin
- [ ] Junction → Cap positive
- [ ] Cap negative → Jack tip
- [ ] Jack sleeve → GND rail

### Software Test

Upload this test code:

```cpp
// Test all 3 channels
#define CT1_PIN 34
#define CT2_PIN 35
#define CT3_PIN 36

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int adc1 = analogRead(CT1_PIN);
  int adc2 = analogRead(CT2_PIN);
  int adc3 = analogRead(CT3_PIN);

  Serial.printf("CH1: %d, CH2: %d, CH3: %d (expected ~2048 each)\\n",
                adc1, adc2, adc3);
  delay(1000);
}
```

**Expected output:**
```
CH1: 2048, CH2: 2048, CH3: 2048 (expected ~2048 each)
```

If any channel reads 0 or 4095, that channel is wired incorrectly!

---

## Bill of Materials

| Qty | Component | Specification | Est. Cost |
|-----|-----------|--------------|-----------|
| 1 | ESP32 DevKit | ESP32-WROOM-32 | $8-12 |
| 1 | Perfboard | 30x22 holes (~8x6cm) | $2-3 |
| 6 | Resistor | 10kΩ ±5% 1/4W | $0.60 |
| 3 | Capacitor | 10µF 25V electrolytic | $0.45 |
| 3 | 3.5mm Jack | PCB mount stereo jack | $3-6 |
| 2 | Female headers | 40-pin 2.54mm (break to 15) | $1 |
| 3 | CT Sensor | SCT013-050 (50A/1V) with 3.5mm plug | $36-45 |
| - | Wire | 22AWG solid core | $2 |
| 1 | Enclosure | With cable glands (optional) | $10-15 |

**Total:** ~$65-85 for complete 3-channel system

---

## Code Updates for 3 Channels

You'll need to update your ESP32_CurrentSensor.ino to support 3 channels:

```cpp
// Define pins for 3 channels
#define CT1_PIN 34
#define CT2_PIN 35
#define CT3_PIN 36

void loop() {
  framework.update();

  if (framework.shouldPublish()) {
    // Read all 3 current sensors
    float current1 = readCurrentRMS(CT1_PIN);
    float current2 = readCurrentRMS(CT2_PIN);
    float current3 = readCurrentRMS(CT3_PIN);

    // Publish to MQTT
    framework.publish("current1_amps", current1);
    framework.publish("current2_amps", current2);
    framework.publish("current3_amps", current3);
  }
}
```

---

## Physical Layout Notes

### Component Spacing

- **Channels spaced 5 rows apart:** Enough room to work, not wasteful
- **3.5mm jacks at board edge:** Columns 19-22, easy cable access
- **ESP32 on left, components on right:** Clean layout, easy assembly

### Orientation for Enclosure

```
┌─────────────────────────────────┐
│  ESP32 (USB down)               │
│                                 │
│                      CT1 Jack→ ○│
│                                 │
│                      CT2 Jack→ ○│
│                                 │
│                      CT3 Jack→ ○│
└─────────────────────────────────┘
```

Mount in enclosure with:
- USB port accessible at bottom
- 3 jacks accessible at right edge
- Board secured with standoffs/hot glue

---

## Troubleshooting

### Problem: One channel works, others don't

**Diagnosis:** Test each channel independently
- Measure voltage at each junction (should all be 1.65V)
- Check ADC readings (should all be ~2048)
- Verify GPIO pin assignments in code

### Problem: All channels read identical values

**Diagnosis:** Channels are shorted together
- Check for solder bridges on bottom
- Verify each GPIO wire goes to correct pin

### Problem: Readings drift over time

**Diagnosis:** Thermal issues or poor solder joints
- Check all capacitor connections
- Verify stable 3.3V power rail
- May need heat management in enclosure

---

## Build Time Estimate

- **First time:** 4-6 hours (testing each channel)
- **With practice:** 2-3 hours

---

## Summary

✅ **Board size:** 30 x 22 holes (76mm x 56mm)
✅ **Layout:** Efficient, room to work, not wasteful
✅ **3 channels:** Independent circuits, shared power
✅ **Professional:** Removable CT sensors via 3.5mm jacks
✅ **Testable:** Build and test each channel independently

This is a **production-quality design** that will serve you well!

Good luck with the build! 🛠️

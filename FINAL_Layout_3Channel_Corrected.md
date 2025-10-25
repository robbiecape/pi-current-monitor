# ESP32 3-Channel Current Monitor - FINAL CORRECTED LAYOUT

## Board Size (CORRECTED)

**30 columns wide x 26 rows tall**
**Physical size: 76mm x 66mm (7.6cm x 6.6cm)**

---

## 3.5mm Jack Pinout (Your Specific Jack)

**Dimensions:** 5 rows tall x 3 columns wide
**Viewing from BOTTOM of board (solder side, upside down orientation):**

```
Column: 1   2   3
Row 1:  ○   ○   ○  (unused)
Row 2:  ○   ○   ○  (unused)
Row 3:  ○   ○   ●  ← Pin 3: CT Red wire (GND)
Row 4:  ○   ○   ○  (unused)
Row 5:  ●   ○   ○  ← Pin 1: CT White wire (Signal)
```

**Connections we use:**
- **Row 5, Column 1** → White wire (signal) → connects to capacitor negative
- **Row 3, Column 3** → Red wire (GND) → connects to GND rail
- **Other 3 pins** → not connected

---

## Complete Board Layout Overview

### Section Breakdown:

```
Rows 1-2:    Power rails (3.3V and GND)
Rows 3:      Empty
Rows 4-15:   ESP32 socket (left side)
Rows 4-10:   Channel 1 - GPIO34 (right side)
Rows 11-17:  Channel 2 - GPIO35 (right side)
Rows 18-24:  Channel 3 - GPIO36 (right side)
Rows 25-26:  Empty (future expansion)
```

### Board Regions:

**Columns 1-16:** ESP32 and power distribution
**Columns 17-24:** Component area (resistors, caps)
**Columns 25-30:** Jack area (jacks can overhang edge)

---

## Detailed Component Positions

### Power Rails (Rows 1-2)

**Row 1 - 3.3V Rail:**
- Horizontal wire from Column 1 to Column 20
- Distributes 3.3V to all components

**Row 2 - GND Rail:**
- Horizontal wire from Column 1 to Column 30 (full width)
- Ground reference for entire board

---

### ESP32 Socket (Rows 4-15, Columns 2-16)

**Female Header Row 1:** Row 4, Columns 2-16 (15 pins)
**Female Header Row 2:** Row 15, Columns 2-16 (15 pins)

**After installing, identify these pins with multimeter:**
- 3.3V pin (mark column number)
- GND pin (mark column number)
- GPIO34 pin (mark column number)
- GPIO35 pin (mark column number)
- GPIO36 pin (mark column number)

---

## CHANNEL 1 - GPIO34 (Rows 4-10, Columns 17-30)

### Component Positions:

**Voltage Divider (Row 4):**
- **R1 (10kΩ):**
  - Leg 1: Row 4, Column 17
  - Leg 2: Row 4, Column 18 (junction)
- **R2 (10kΩ):**
  - Leg 1: Row 4, Column 18 (junction, shares hole with R1)
  - Leg 2: Row 4, Column 19

**Capacitor (Rows 5-6, Column 24):**
- **Positive (+) lead:** Row 5, Column 24
- **Negative (-) lead:** Row 6, Column 24
- **Polarity:** White stripe on cap = negative (bottom)

**3.5mm Jack (Rows 5-9, Columns 27-29):**
- Jack body: 5 rows tall, 3 columns wide
- Mounted at right edge (can overhang)
- **Pin connections (viewed from bottom):**
  - Row 9, Column 27 → White wire → Cap negative (Row 6, Col 24)
  - Row 7, Column 29 → Red wire → GND rail (Row 2)

### Wiring (Bottom Side):

1. **R1 top to 3.3V:** Row 4, Col 17 → Row 1, Col 17
2. **R2 bottom to GND:** Row 4, Col 19 → Row 2, Col 19
3. **Junction to GPIO34:** Row 4, Col 18 → GPIO34 pin (wherever marked)
4. **Junction to Cap+:** Row 4, Col 18 → Row 5, Col 24
5. **Cap- to Jack signal:** Row 6, Col 24 → Row 9, Col 27 (jack pin)
6. **Jack GND to rail:** Row 7, Col 29 (jack pin) → Row 2, Col 29

---

## CHANNEL 2 - GPIO35 (Rows 11-17, Columns 17-30)

### Component Positions:

**Voltage Divider (Row 11):**
- **R1:** Row 11, Col 17 → Col 18 (junction)
- **R2:** Row 11, Col 18 (junction) → Col 19

**Capacitor (Rows 12-13, Column 24):**
- **Positive (+):** Row 12, Column 24
- **Negative (-):** Row 13, Column 24

**3.5mm Jack (Rows 12-16, Columns 27-29):**
- Jack body: 5 rows tall, 3 columns wide
- **Pin connections (viewed from bottom):**
  - Row 16, Column 27 → White wire → Cap negative (Row 13, Col 24)
  - Row 14, Column 29 → Red wire → GND rail (Row 2)

### Wiring (Bottom Side):

7. **R1 top to 3.3V:** Row 11, Col 17 → Row 1, Col 17
8. **R2 bottom to GND:** Row 11, Col 19 → Row 2, Col 19
9. **Junction to GPIO35:** Row 11, Col 18 → GPIO35 pin
10. **Junction to Cap+:** Row 11, Col 18 → Row 12, Col 24
11. **Cap- to Jack signal:** Row 13, Col 24 → Row 16, Col 27
12. **Jack GND to rail:** Row 14, Col 29 → Row 2, Col 29

---

## CHANNEL 3 - GPIO36 (Rows 18-24, Columns 17-30)

### Component Positions:

**Voltage Divider (Row 18):**
- **R1:** Row 18, Col 17 → Col 18 (junction)
- **R2:** Row 18, Col 18 (junction) → Col 19

**Capacitor (Rows 19-20, Column 24):**
- **Positive (+):** Row 19, Column 24
- **Negative (-):** Row 20, Column 24

**3.5mm Jack (Rows 19-23, Columns 27-29):**
- Jack body: 5 rows tall, 3 columns wide
- **Pin connections (viewed from bottom):**
  - Row 23, Column 27 → White wire → Cap negative (Row 20, Col 24)
  - Row 21, Column 29 → Red wire → GND rail (Row 2)

### Wiring (Bottom Side):

13. **R1 top to 3.3V:** Row 18, Col 17 → Row 1, Col 17
14. **R2 bottom to GND:** Row 18, Col 19 → Row 2, Col 19
15. **Junction to GPIO36:** Row 18, Col 18 → GPIO36 pin
16. **Junction to Cap+:** Row 18, Col 18 → Row 19, Col 24
17. **Cap- to Jack signal:** Row 20, Col 24 → Row 23, Col 27
18. **Jack GND to rail:** Row 21, Col 29 → Row 2, Col 29

---

## ESP32 Power Connections

19. **ESP32 3.3V pin → 3.3V rail** (Row 1)
20. **ESP32 GND pin → GND rail** (Row 2)

---

## Complete Wiring List (20 wires total)

### Power Infrastructure:
1. 3.3V rail: Row 1, horizontal wire Col 1→20
2. GND rail: Row 2, horizontal wire Col 1→30

### Channel 1 (6 wires):
3. R1 to 3.3V: (R4,C17) → (R1,C17)
4. R2 to GND: (R4,C19) → (R2,C19)
5. Junction to GPIO34: (R4,C18) → GPIO34 pin
6. Junction to Cap+: (R4,C18) → (R5,C24)
7. Cap- to Jack signal: (R6,C24) → (R9,C27)
8. Jack GND to rail: (R7,C29) → (R2,C29)

### Channel 2 (6 wires):
9. R1 to 3.3V: (R11,C17) → (R1,C17)
10. R2 to GND: (R11,C19) → (R2,C19)
11. Junction to GPIO35: (R11,C18) → GPIO35 pin
12. Junction to Cap+: (R11,C18) → (R12,C24)
13. Cap- to Jack signal: (R13,C24) → (R16,C27)
14. Jack GND to rail: (R14,C29) → (R2,C29)

### Channel 3 (6 wires):
15. R1 to 3.3V: (R18,C17) → (R1,C17)
16. R2 to GND: (R18,C19) → (R2,C19)
17. Junction to GPIO36: (R18,C18) → GPIO36 pin
18. Junction to Cap+: (R18,C18) → (R19,C24)
19. Cap- to Jack signal: (R20,C24) → (R23,C27)
20. Jack GND to rail: (R21,C29) → (R2,C29)

### ESP32 Power (2 wires):
21. ESP32 3.3V → (R1)
22. ESP32 GND → (R2)

**Total: 22 wires on bottom side**

---

## Visual Component Layout (Simplified)

```
Top View:

Col:  1-2   ...  16-17  18-19     24        27-29
    ┌─────────────────────────────────────────────┐
R1  │3.3V═══════════════════════════════════GND  │ Power rails
R2  │GND══════════════════════════════════════GND│
R3  │                                             │
R4  │【ESP32 Header 1】 R1-●-R2                   │ CH1 resistors
R5  │                           Cap+       【Jack│ CH1 cap+ & jack
R6  │  3V  ... 34 ... GN        Cap-         1  │ CH1 cap- & jack
R7  │                                        】  │ CH1 jack
R8  │                                             │
R9  │     [ESP32 body]                            │
R10 │                                             │
R11 │                    R1-●-R2                  │ CH2 resistors
R12 │                           Cap+       【Jack│ CH2 cap+ & jack
R13 │                           Cap-         2  │ CH2 cap- & jack
R14 │                                        】  │ CH2 jack
R15 │【ESP32 Header 2】                           │
R16 │  .. 35 .. 36 ..                             │ GPIO35, 36
R17 │                                             │
R18 │                    R1-●-R2                  │ CH3 resistors
R19 │                           Cap+       【Jack│ CH3 cap+ & jack
R20 │                           Cap-         3  │ CH3 cap- & jack
R21 │                                        】  │ CH3 jack
R22-│                                             │
R26 │                                             │ Future expansion
    └─────────────────────────────────────────────┘
      ↑                    ↑      ↑          ↑
    ESP32                Voltage  Caps      Jacks
    socket               dividers
```

---

## Step-by-Step Assembly

### Step 1: Install ESP32 Socket

1. Break two 15-pin female header strips
2. Position at Row 4 and Row 15, Columns 2-16
3. Insert ESP32 to align, then tape in place
4. Solder all 30 pins from bottom
5. Remove ESP32 and trim pins flush
6. **Identify GPIO pins with multimeter and mark with sharpie!**

### Step 2: Create Power Rails

1. **3.3V rail:** Solder wire along Row 1, Columns 1-20
2. **GND rail:** Solder wire along Row 2, Columns 1-30
3. Connect ESP32 3.3V pin to Row 1
4. Connect ESP32 GND pin to Row 2

### Step 3: Build Channel 1

**Resistors:**
1. Insert R1: Row 4, Col 17→18
2. Insert R2: Row 4, Col 18→19 (share junction hole)
3. Solder from bottom
4. Wire R1 to 3.3V rail
5. Wire R2 to GND rail

**Test voltage divider:**
- Power on
- Measure junction (R4,C18) to GND
- Should read **1.65V** ✅

**Capacitor:**
1. Check polarity (white stripe = negative)
2. Insert: Positive at Row 5 Col 24, Negative at Row 6 Col 24
3. Solder from bottom
4. Wire Cap+ to junction (R4,C18)

**3.5mm Jack:**
1. Position jack at Rows 5-9, Columns 27-29 (edge of board)
2. Solder all 5 pins
3. From bottom, identify:
   - Signal pin (Row 9, Col 27)
   - GND pin (Row 7, Col 29)
4. Wire signal pin to Cap- (R6,C24)
5. Wire GND pin to GND rail (R2)

**GPIO Connection:**
1. Wire junction (R4,C18) to GPIO34 pin

**Test Channel 1:**
- Upload test code
- ADC should read ~2048 ✅

### Step 4: Build Channel 2

Repeat Step 3 using:
- Rows 11-17 (instead of 4-10)
- GPIO35 pin (instead of GPIO34)
- Same column positions

### Step 5: Build Channel 3

Repeat Step 3 using:
- Rows 18-24 (instead of 4-10)
- GPIO36 pin (instead of GPIO34)
- Same column positions

---

## Testing Each Channel

### Voltage Test (before adding capacitor):

Measure junction to GND: **1.65V DC** (±0.2V)

### ADC Test (no CT connected):

```cpp
int adc = analogRead(34); // or 35, 36
Serial.printf("CH: %d (expected ~2048)\n", adc);
```

Expected: **~2048** (±100)
- If 0 → voltage divider broken
- If 4095 → short circuit somewhere

### CT Sensor Test (with load):

Plug CT sensor into jack, clamp around live wire, compare to Kill-A-Watt.

---

## Bill of Materials (CORRECTED)

| Qty | Item | Specification | Est. Cost |
|-----|------|---------------|-----------|
| 1 | Perfboard | 30x26 holes (8x7cm) | $2-3 |
| 1 | ESP32 DevKit | ESP32-WROOM-32 | $8-12 |
| 2 | Female headers | 40-pin 2.54mm (break to 15) | $1 |
| 6 | Resistors | 10kΩ ±5% 1/4W | $0.60 |
| 3 | Capacitors | 10µF 25V electrolytic | $0.45 |
| 3 | 3.5mm jacks | PCB mount stereo, 5x3 holes | $3-6 |
| 1 | Wire | 22AWG solid core (100ft) | $8-12 |
| 3 | CT sensors | SCT013-050 with 3.5mm plug | $36-45 |

**Total: ~$60-80**

---

## Code Updates for 3 Channels

```cpp
#define CT1_PIN 34
#define CT2_PIN 35
#define CT3_PIN 36

// Per-device calibration (add entries for each channel)
struct DeviceCalibration {
  const char* mac;
  float ct1Ratio;
  float ct2Ratio;
  float ct3Ratio;
};

DeviceCalibration calibrations[] = {
  {"781C3CCB7270", 31.4, 31.4, 31.4},  // Adjust per channel after testing
};

void loop() {
  framework.update();

  if (framework.shouldPublish()) {
    float current1 = readCurrentRMS(CT1_PIN, CT1_RATIO);
    float current2 = readCurrentRMS(CT2_PIN, CT2_RATIO);
    float current3 = readCurrentRMS(CT3_PIN, CT3_RATIO);

    framework.publish("current1_amps", current1);
    framework.publish("current2_amps", current2);
    framework.publish("current3_amps", current3);
  }
}
```

---

## Summary

✅ **Board size:** 30x26 holes (76mm x 66mm)
✅ **Jack dimensions:** 5 rows x 3 columns (CORRECTED)
✅ **Jack pinout:** Row 5 Col 1 = signal, Row 3 Col 3 = GND
✅ **Channel spacing:** 7 rows per channel
✅ **Wiring:** 22 wires total on bottom
✅ **Build strategy:** One channel at a time, test each

This is the accurate, production-ready layout! 🛠️

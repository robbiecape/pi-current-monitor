# ESP32 3-Channel Current Monitor - CLEAR Layout Guide

## Board Size

**30 columns wide x 22 rows tall**
**Physical size: 76mm x 56mm (7.6cm x 5.6cm)**

---

## Visual Overview (Simple)

Imagine looking down at your perfboard from above:

```
┌─────────────────────────────────────────┐
│ Power Rails (top)                       │
│                                         │
│ ┌─────────────┐                        │
│ │   ESP32     │         CH1 ○ Jack     │
│ │   Socket    │         Components     │
│ │             │                        │
│ │  (USB→)     │         CH2 ○ Jack     │
│ │             │         Components     │
│ │             │                        │
│ └─────────────┘         CH3 ○ Jack     │
│                         Components     │
│                                         │
└─────────────────────────────────────────┘
```

**Left side:** ESP32 with socket
**Right side:** 3 channels of components, stacked vertically
**Top:** Power distribution wires

---

## Section 1: Power Rails (Rows 1-2)

### What to do:
Create two horizontal "bus" wires at the very top of the board.

**Row 1 - 3.3V Power Rail:**
- Solder a wire horizontally from Column 1 to Column 15
- This distributes 3.3V power to all components

**Row 2 - Ground (GND) Rail:**
- Solder a wire horizontally from Column 1 to Column 30 (entire width)
- This is your ground reference

### Why:
These wires act like "power strips" - you tap into them whenever you need 3.3V or GND.

---

## Section 2: ESP32 Socket (Rows 4-15, Columns 2-16)

### What to do:
Install two rows of female header pins for the ESP32 to plug into.

**Header Row 1:** Row 4, Columns 2-16 (15 pins total)
**Header Row 2:** Row 15, Columns 2-16 (15 pins total)

### Position:
- Left side of board
- USB port will face toward the right
- 11 rows of space between the two header rows

### Important Pins to Identify:
After installing headers, plug in your ESP32 and use a multimeter to find which **column** each pin is in:

- **3.3V pin** → probably around Column 2-3
- **GPIO34 pin** → probably around Column 8
- **GPIO35 pin** → probably around Column 8 (on other row)
- **GPIO36 pin** → probably around Column 12 (on other row)
- **GND pin** → probably around Column 14

**Mark these columns with a sharpie!** You'll need them later.

---

## Section 3: Channel 1 (GPIO34) - Rows 4-7, Columns 17-22

This is the first CT sensor circuit. Here's what goes where:

### Components Layout (looking at top of board):

```
Row 4:  [R1]──[Junction]──[R2]     ← Two resistors
Row 5:            [Cap +]          ← Capacitor positive lead
Row 6:            [Cap -]          ← Capacitor negative lead
Rows 6-7:      [3.5mm Jack]        ← Jack for CT sensor
```

### Exact Positions:

**R1 (10kΩ resistor):**
- Leg 1: Row 4, Column 17
- Leg 2: Row 4, Column 18 (this is the "junction")

**R2 (10kΩ resistor):**
- Leg 1: Row 4, Column 18 (shares the junction hole with R1)
- Leg 2: Row 4, Column 19

**10µF Capacitor:**
- Positive (+) lead: Row 5, Column 19
- Negative (-) lead: Row 6, Column 19
- **POLARITY CRITICAL:** White stripe on cap = negative side

**3.5mm PCB Jack:**
- Mounted at Rows 6-7, Columns 19-22 (takes up ~4 columns of space)
- **Tip pin** connects to Cap negative (Row 6, Column 19)
- **Sleeve pin** connects to GND

### Wiring (on bottom of board):

**Wire 1:** R1 top (Row 4, Col 17) → 3.3V rail (Row 1)
**Wire 2:** R2 bottom (Row 4, Col 19) → GND rail (Row 2)
**Wire 3:** Junction (Row 4, Col 18) → ESP32 GPIO34 pin (wherever you marked it)
**Wire 4:** Junction (Row 4, Col 18) → Cap positive (Row 5, Col 19)
**Wire 5:** Jack sleeve → GND rail (Row 2)

---

## Section 4: Channel 2 (GPIO35) - Rows 9-12, Columns 17-22

This is identical to Channel 1, just 5 rows lower.

### Components Layout:

```
Row 9:  [R1]──[Junction]──[R2]     ← Two resistors
Row 10:           [Cap +]          ← Capacitor positive
Row 11:           [Cap -]          ← Capacitor negative
Rows 11-12:    [3.5mm Jack]        ← Jack for CT sensor
```

### Exact Positions:

**R1:** Row 9, Columns 17→18
**R2:** Row 9, Columns 18→19 (shares junction at col 18)
**Cap:** Positive at Row 10 Col 19, Negative at Row 11 Col 19
**Jack:** Rows 11-12, Columns 19-22

### Wiring (on bottom):

**Wire 6:** R1 top → 3.3V rail
**Wire 7:** R2 bottom → GND rail
**Wire 8:** Junction → ESP32 GPIO35 pin (wherever you marked it)
**Wire 9:** Junction → Cap positive
**Wire 10:** Jack sleeve → GND rail

---

## Section 5: Channel 3 (GPIO36) - Rows 14-17, Columns 17-22

Same as Channels 1 and 2, just 5 rows lower again.

### Components Layout:

```
Row 14: [R1]──[Junction]──[R2]     ← Two resistors
Row 15:           [Cap +]          ← Capacitor positive
Row 16:           [Cap -]          ← Capacitor negative
Rows 16-17:    [3.5mm Jack]        ← Jack for CT sensor
```

### Exact Positions:

**R1:** Row 14, Columns 17→18
**R2:** Row 14, Columns 18→19 (shares junction at col 18)
**Cap:** Positive at Row 15 Col 19, Negative at Row 16 Col 19
**Jack:** Rows 16-17, Columns 19-22

### Wiring (on bottom):

**Wire 11:** R1 top → 3.3V rail
**Wire 12:** R2 bottom → GND rail
**Wire 13:** Junction → ESP32 GPIO36 pin (wherever you marked it)
**Wire 14:** Junction → Cap positive
**Wire 15:** Jack sleeve → GND rail

---

## Section 6: ESP32 Power Connections

Connect the ESP32 to your power rails.

**Wire 16:** ESP32 3.3V pin → 3.3V rail (Row 1)
**Wire 17:** ESP32 GND pin → GND rail (Row 2)

---

## Complete Wiring Summary

Here's every wire you need to solder on the **bottom** of the board:

### Power Rails (create these first)
1. 3.3V rail: Row 1, horizontal wire from Column 1→15
2. GND rail: Row 2, horizontal wire from Column 1→30

### Channel 1 (5 wires)
3. R1 top (R4,C17) → 3.3V rail (R1)
4. R2 bottom (R4,C19) → GND rail (R2)
5. Junction (R4,C18) → GPIO34 pin
6. Junction (R4,C18) → Cap+ (R5,C19)
7. Jack sleeve → GND rail (R2)

### Channel 2 (5 wires)
8. R1 top (R9,C17) → 3.3V rail (R1)
9. R2 bottom (R9,C19) → GND rail (R2)
10. Junction (R9,C18) → GPIO35 pin
11. Junction (R9,C18) → Cap+ (R10,C19)
12. Jack sleeve → GND rail (R2)

### Channel 3 (5 wires)
13. R1 top (R14,C17) → 3.3V rail (R1)
14. R2 bottom (R14,C19) → GND rail (R2)
15. Junction (R14,C18) → GPIO36 pin
16. Junction (R14,C18) → Cap+ (R15,C19)
17. Jack sleeve → GND rail (R2)

### ESP32 Power (2 wires)
18. ESP32 3.3V pin → 3.3V rail (R1)
19. ESP32 GND pin → GND rail (R2)

**Total: 19 wires**

---

## Assembly Order (Step-by-Step)

### Step 1: Install ESP32 Socket
- Solder female headers at Rows 4 and 15, Columns 2-16
- Plug ESP32 in to test fit
- Identify and mark GPIO pins with sharpie

### Step 2: Create Power Rails
- Solder 3.3V rail wire (Row 1)
- Solder GND rail wire (Row 2)
- Connect ESP32 3.3V and GND pins to rails

### Step 3: Build Channel 1
- Install R1 and R2 (Row 4, Cols 17-19)
- Wire R1 to 3.3V, R2 to GND
- Test voltage at junction (should read 1.65V) ✅
- Install capacitor (Rows 5-6, Col 19)
- Wire junction to Cap+
- Wire junction to GPIO34
- Install 3.5mm jack (Rows 6-7, Cols 19-22)
- Wire jack sleeve to GND
- Test Channel 1 with code ✅

### Step 4: Build Channel 2
- Repeat Step 3 using Rows 9-12 and GPIO35

### Step 5: Build Channel 3
- Repeat Step 3 using Rows 14-17 and GPIO36

### Step 6: Final Testing
- Test all 3 channels simultaneously
- Verify all ADC readings ~2048
- Plug in CT sensors and test with actual current

---

## Physical Dimensions Reference

**Spacing between components:**
- Channels are 5 rows apart (plenty of room to work)
- Components in each channel span ~3-4 rows
- 3.5mm jacks are at the right edge (easy cable access)

**Component footprints:**
- Resistors: 2 holes apart (fits in 1 row)
- Capacitor: 2 rows tall (vertical orientation)
- 3.5mm jack: 2 rows tall, ~4 columns wide

---

## Testing Each Channel

Before moving to the next channel, test the current one:

**Voltage Test (power on, no CT connected):**
- Measure voltage at junction (R4/C18, R9/C18, or R14/C18)
- Should read **1.65V DC**
- If wrong, fix before continuing!

**Software Test:**
```cpp
void loop() {
  int adc = analogRead(34); // or 35, 36
  Serial.printf("ADC: %d (expected ~2048)\n", adc);
  delay(1000);
}
```

Expected: **ADC ~2048** (±100)
- If 0 or 4095 → circuit wired wrong!

---

## Common Questions

### Q: What is a "junction"?
A: The point where R1 and R2 meet. Both resistor legs go into the same perfboard hole. This also connects to GPIO and Cap+.

### Q: How do I create the power rails?
A: Strip a long piece of wire, thread it through holes on Row 1 (or Row 2), and solder at each hole to create a continuous connection across multiple holes.

### Q: Do wires go on top or bottom?
A: **Components on top, wires on bottom.** All 19 wires are soldered on the bottom side of the perfboard.

### Q: What if my ESP32 pins are in different columns?
A: That's fine! Just identify where YOUR GPIO34/35/36 pins are and route wires to those specific holes. The component side (right) stays the same.

### Q: Can I test one channel before building the others?
A: **YES! Highly recommended.** Build Channel 1, test it completely, then build Channel 2, etc.

---

## Bill of Materials

| Qty | Item | Specification |
|-----|------|---------------|
| 1 | Perfboard | 30x22 holes (8x6cm) |
| 1 | ESP32 | ESP32-WROOM-32 DevKit |
| 2 | Female headers | 40-pin 2.54mm (break to 15-pin) |
| 6 | Resistors | 10kΩ ±5% 1/4W |
| 3 | Capacitors | 10µF 25V electrolytic |
| 3 | 3.5mm jacks | PCB mount stereo jack |
| 1 | Wire | 22AWG solid core (100ft spool) |
| 3 | CT sensors | SCT013-050 with 3.5mm plug |

---

## Summary

✅ **Board layout:** ESP32 on left, 3 channels stacked on right
✅ **Build strategy:** One channel at a time, test each before continuing
✅ **Wiring:** All on bottom, 19 wires total
✅ **Size:** 30x22 holes = tight but workable

This is a production-quality design that will work great! Take your time, test at each step, and you'll have a reliable 3-channel current monitor.

Good luck! 🛠️

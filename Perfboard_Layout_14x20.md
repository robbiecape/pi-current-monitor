# ESP32 Current Monitor - 14x20 Hole Perfboard Layout

## Your Board Specifications
- **Board holes:** 14 tall x 20 wide
- **Physical size:** ~36mm x 51mm
- **Hole spacing:** 2.54mm (standard)
- **ESP32 footprint:** 15 pins per row, 11 holes between rows (15 long x 11 wide)
- **Perfboard type:** Isolated holes (no pre-connected rails)

**IMPORTANT:** With ESP32 taking 15x11 holes and your board being 14x20, space is VERY tight!

**Orientation:** 20 holes horizontal (width), 14 holes vertical (height)

---

## Component Placement - Exact Hole Grid

```
Column: 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
      ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
Row 1 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 2 │3V│══│══│══│══│══│══│══│══│══│══│══│══│══│══│══│══│══│══│GN│ Power rails
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 3 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 4 │  │  │  │[ ESP32 SOCKET - HEADER ROW 1 ]│  │  │  │  │  │  │ Socket starts
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 5 │  │  │  │3V│  │  │  │  │34│  │  │  │GN│  │  │  │  │  │  │  │ ESP32 pins
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 6 │  │  │  │  │[ ESP32 USB PORT FACES RIGHT →]│  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 7 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 8 │  │  │  │[ ESP32 SOCKET - HEADER ROW 2 ]│  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 9 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row10 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row11 │  │R1│──│●│──│R2│  │  │  │  │  │  │  │  │  │  │  │  │  │  │ Resistors
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row12 │  │  │  │+ │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │ Cap positive
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row13 │  │  │  │- │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │ Cap negative
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row14 │  │  │GN│CT│GN│  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │ CT connection
      └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
```

**Notes:**
- 3V = 3.3V connection
- GN = GND connection
- 34 = GPIO34 connection
- ● = Junction point (R1/R2/GPIO34)
- + = Capacitor positive lead
- - = Capacitor negative lead
- CT = CT sensor signal wire

---

## Detailed Component Positions

### Row 2: Power Distribution Rails
```
Column 1: 3.3V rail start
Column 20: GND rail end
Run wires horizontally across entire row for power distribution
```

### Rows 4-8: ESP32 Socket
```
Row 4: Female header row 1 (pins 1-15 or 1-19 depending on ESP32)
Row 8: Female header row 2 (pins 1-15 or 1-19)

Suggested position: Columns 4-13 (centered, leaves room on sides)

Key pins to identify:
- Column 4: 3.3V pin
- Column 9: GPIO34 pin
- Column 13: GND pin
(Exact columns depend on your specific ESP32 model)
```

### Row 11: Voltage Divider Resistors
```
R1 (10kΩ):
  - Leg 1: Column 2, Row 11 → connects to 3.3V rail (Row 2, Column 1)
  - Leg 2: Column 4, Row 11 (junction point)

R2 (10kΩ):
  - Leg 1: Column 4, Row 11 (junction point - same hole as R1 leg 2)
  - Leg 2: Column 6, Row 11 → connects to GND rail (Row 2, Column 20)

Junction point (Column 4, Row 11):
  - Connects to GPIO34 pin (Row 5, Column 9) via wire on bottom
```

### Rows 12-13: Capacitor (10µF)
```
Positive (+): Column 4, Row 12
  - Connects to junction (Column 4, Row 11) via short wire

Negative (-): Column 4, Row 13
  - Connects to CT signal wire (Column 4, Row 14)

IMPORTANT: Check polarity! White stripe = negative side
```

### Row 14: CT Sensor Connection
```
Column 3: GND pad → wire to GND rail
Column 4: CT signal (white wire) → connects to Cap negative (Row 13)
Column 5: GND pad → wire to GND rail (strain relief - both sides grounded)
```

---

## Wire Routing Guide (Bottom Side)

After soldering components, run these wires on the **bottom** of the board:

### Power Wires
1. **3.3V rail** (Row 2, Column 1) → R1 top (Row 11, Column 2)
2. **3.3V rail** (Row 2, Column 1) → ESP32 3.3V pin (Row 5, Column 4)
3. **GND rail** (Row 2, Column 20) → R2 bottom (Row 11, Column 6)
4. **GND rail** (Row 2, Column 20) → ESP32 GND pin (Row 5, Column 13)
5. **GND rail** (Row 2, Column 20) → CT GND pads (Row 14, Columns 3 & 5)

### Signal Wires
6. **Junction** (Row 11, Column 4) → GPIO34 pin (Row 5, Column 9)
7. **Junction** (Row 11, Column 4) → Cap positive (Row 12, Column 4)
8. **Cap negative** (Row 13, Column 4) → CT signal pad (Row 14, Column 4)

---

## Assembly Steps

### Step 1: Install ESP32 Socket Headers

1. **Measure your ESP32:**
   - Count pins on each side (usually 15-19)
   - Measure the spacing between rows (usually 8-10 holes)

2. **Break header strips:**
   - Cut two strips to match pin count
   - Example: If 15 pins, cut 2x 15-pin strips

3. **Position on board:**
   - Row 4: First header strip
   - Row 8: Second header strip
   - Center them around Columns 4-13

4. **Alignment trick:**
   - Insert headers into perfboard holes
   - Plug ESP32 into headers (to ensure perfect alignment)
   - Tape in place

5. **Solder:**
   - Flip board over (ESP32 still inserted)
   - Solder all pins on bottom
   - Remove ESP32
   - Trim pins flush

6. **Identify critical pins:**
   - Using a multimeter in continuity mode:
   - Find which socket hole connects to ESP32's 3.3V pin
   - Find which socket hole connects to GPIO34
   - Find which socket hole connects to GND
   - **Mark these with a marker on the perfboard!**

---

### Step 2: Create Power Rails

1. **Strip wire:**
   - Cut ~5cm of 22AWG solid core wire
   - Strip 1cm from each end

2. **Solder 3.3V rail:**
   - Row 2, Column 1 → horizontal across ~10 holes
   - This distributes 3.3V to components

3. **Solder GND rail:**
   - Row 2, Column 20 → horizontal across ~10 holes
   - This distributes GND to components

---

### Step 3: Install Resistors

1. **Bend R1 leads:**
   - Bend to span from Column 2 to Column 4, Row 11
   - Insert: Column 2 (top), Column 4 (junction)
   - Solder from bottom
   - DO NOT trim yet

2. **Bend R2 leads:**
   - Bend to span from Column 4 to Column 6, Row 11
   - Insert: Column 4 (junction, same hole as R1), Column 6 (bottom)
   - Solder from bottom
   - DO NOT trim yet

3. **Wire R1 to 3.3V:**
   - Connect Column 2, Row 11 to 3.3V rail (Row 2)
   - Use short wire on bottom

4. **Wire R2 to GND:**
   - Connect Column 6, Row 11 to GND rail (Row 2)
   - Use short wire on bottom

---

### Step 4: TEST VOLTAGE DIVIDER

**CRITICAL: Test before continuing!**

1. Plug ESP32 into socket
2. Plug USB cable into ESP32
3. Multimeter to DC voltage mode
4. Measure from junction (Row 11, Column 4) to GND

**Expected: 1.65V DC (±0.2V acceptable)**

✅ If correct → Continue to Step 5
❌ If wrong → STOP and troubleshoot:
   - 3.3V reading → R2 not connected to GND
   - 0V reading → R1 not connected to 3.3V
   - Other → Check solder joints, resistor values

---

### Step 5: Install Capacitor

1. **Identify polarity:**
   - White stripe on capacitor = NEGATIVE side
   - Shorter lead = negative

2. **Insert:**
   - Positive (+) lead: Column 4, Row 12
   - Negative (-) lead: Column 4, Row 13
   - Solder from bottom

3. **Wire positive to junction:**
   - Connect Row 12, Column 4 to Row 11, Column 4 (junction)
   - Short vertical wire on bottom

4. **Trim resistor leads** (now that cap is in place)

---

### Step 6: Wire Junction to GPIO34

1. **Measure wire:**
   - From junction (Row 11, Column 4) to GPIO34 pin hole
   - Cut wire 2-3cm longer than needed

2. **Route on bottom:**
   - Solder one end to junction hole
   - Route to GPIO34 socket pin hole
   - Solder other end

3. **Test connection:**
   - Multimeter continuity mode
   - Should beep between junction and GPIO34 pin

---

### Step 7: Create CT Connection Pads

1. **Prepare three solder pads:**
   - Row 14, Column 3: GND
   - Row 14, Column 4: Signal
   - Row 14, Column 5: GND

2. **Tin the pads:**
   - Add small blob of solder to each hole
   - These become solder pads for wires

3. **Wire connections:**
   - Column 3 → GND rail (short wire)
   - Column 4 → Cap negative (Row 13, Column 4)
   - Column 5 → GND rail (short wire)

---

### Step 8: Connect CT Sensor

1. **Cut CT plug off:**
   - Leave 20-30cm of wire for flexibility
   - Strip red and white wires ~5mm each

2. **Tin the wires:**
   - Add solder to stripped ends

3. **Solder to pads:**
   - CT Red wire → Row 14, Column 3 (GND pad)
   - CT White wire → Row 14, Column 4 (Signal pad)

4. **Strain relief:**
   - Hot glue around wires at board edge
   - Prevents solder joints from breaking

---

## Visual Wiring Diagram (Bottom View)

```
Bottom of board (solder side):

     3.3V Rail ═══════════════════════════════════════
         ║                           ║
         ║ (to R1)                   ║ (to ESP32 3V3)
         ║                           ║
    [R1]─●─[R2]                     ESP32
         ║  ║                       Socket
         ║  ║ (to GND)              Pins
    GPIO34  ║
     Wire   ║
         ║  ║
      [Cap+]║
         ║  ║
      [Cap-]║
         ║  ║
    CT Signal
         ║  ║
     GND Rail ═══════════════════════════════════════
```

---

## Testing Checklist

### Visual Inspection
- [ ] No solder bridges between pins
- [ ] All solder joints shiny (not dull/cracked)
- [ ] Capacitor stripe (negative) faces DOWN (away from GPIO34)
- [ ] Resistors flat against board
- [ ] No loose components

### Electrical Tests (Power OFF)

**Continuity tests (multimeter beep mode):**

- [ ] 3.3V rail → R1 top
- [ ] R1 bottom → R2 top (junction)
- [ ] R2 bottom → GND rail
- [ ] Junction → GPIO34 pin
- [ ] Junction → Cap positive
- [ ] Cap negative → CT signal pad
- [ ] CT GND pads → GND rail

### Power-On Tests (USB plugged in)

**Voltage measurements (DC mode, reference to GND):**

| Test Point | Expected Voltage |
|------------|-----------------|
| 3.3V rail | 3.25 - 3.35V |
| Junction (R1/R2) | 1.45 - 1.65V |
| GPIO34 pin | 1.45 - 1.65V |
| Cap positive | 1.45 - 1.65V |

**⚠️ If any voltage is wrong, STOP and troubleshoot!**

### Software Test

1. Upload ESP32_CurrentSensor.ino
2. Open Serial Monitor (115200 baud)
3. Look for: "ADC Bias Test - Average ADC: ~2048"

**Expected readings:**
```
ADC Bias Test - Average ADC: 2048.0 (expected ~2048), Voltage: 1.650V (expected ~1.65V)
```

**Troubleshooting ADC readings:**
- ADC = 0 → Voltage divider broken or not connected
- ADC = 4095 → Short circuit or wrong wiring
- ADC = 2048 ✅ → Circuit working correctly!

---

## Troubleshooting Guide

### Problem: Can't fit ESP32 on board

**Solution:**
- Make sure you're using orientation 20-holes-wide x 14-holes-tall
- ESP32 width (~10 holes) should fit in the 20-hole dimension
- Use female header sockets, not male pins

---

### Problem: Not enough room for components

**Solution:**
- Mount ESP32 socket at Rows 4-8 (upper part of board)
- This leaves Rows 11-14 for resistors/capacitor/CT connection
- Use bottom side for all wire routing

---

### Problem: Junction point is crowded

**Solution:**
- R1, R2, GPIO34 wire, and Cap+ wire all meet here
- Use single hole for junction if possible, or
- Create star junction with small wire loop on bottom

---

### Problem: GPIO34 reads wrong voltage

**Diagnose:**
- 3.3V → R2 not connected to GND
- 0V → R1 not connected to 3.3V
- ~1.65V ✅ → Correct!

---

## Dimensions Reference

Your board:
```
20 holes × 2.54mm = 50.8mm (width)
14 holes × 2.54mm = 35.6mm (height)

Total: 35.6mm × 50.8mm perfboard
```

Components:
```
ESP32: 25mm wide, 48mm long (fits as 10 holes × ~19 holes)
10kΩ resistor: 6mm long
10µF cap: 5mm diameter, 11mm tall
Female headers: 2.54mm pitch, 8.5mm tall
```

**The fit is tight but doable!**

---

## Build Time Estimate

- First time: 2-3 hours
- With practice: 1 hour

---

## Final Notes

This is a **compact build** for a 14x20 perfboard. The components will be close together, so:

1. **Take your time** - rushing leads to mistakes
2. **Test incrementally** - especially the voltage divider
3. **Double-check polarity** - capacitor must be correct
4. **Use bottom side** - for all wire routing to keep top clean

Good luck with your build! 🛠️

# ESP32 Current Monitor - Realistic 14x20 Perfboard Layout

## Critical Dimensions

**Your perfboard:** 14 rows x 20 columns (isolated holes)
**Your ESP32:** 15 pins/row, 11 holes between rows

### The Problem

Your ESP32 won't fit! Here's why:

```
ESP32 needs:     Your board has:     Result:
15 holes long    20 holes wide       ✅ Fits (5 holes left)
11 holes wide    14 holes tall       ✅ Fits (3 holes left)

BUT: Only 3 rows available for ALL components!
```

---

## Recommendation: Get a Bigger Board

**Minimum recommended:** 20x30 holes (or 18x25)

**OR:** Alternative approach below if you must use 14x20

---

## Alternative: Vertical Component Mounting (14x20 Board)

If you MUST use this board, mount components **vertically** (standing up) to save space.

### Layout Option 1: Extremely Compact

```
Column: 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
      ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
Row 1 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │R1│R2│  │  │  │ Resistors here
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 2 │  │【 ESP32 FEMALE HEADER ROW 1 - 15 pins  】│●│+ │  │  │  │ Junction & Cap
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 3 │  │  │ (ESP32 socket continues for 11 rows) │  │- │CT│  │  │ Cap bottom & CT
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 4 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 5 │  │3V│  │  │  │  │  │  │34│  │  │  │  │GN│  │  │  │  │  │  │ Pin connections
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 6 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 7 │  │  │    ESP32 USB PORT FACES RIGHT →      │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 8 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row 9 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row10 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row11 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row12 │  │【 ESP32 FEMALE HEADER ROW 2 - 15 pins  】│  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row13 │  │  │                                       │  │  │  │  │  │
      ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
Row14 │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
      └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

Legend:
  3V = 3.3V pin     34 = GPIO34 pin     GN = GND pin
  R1, R2 = Resistors (standing vertical)
  ● = Junction point    + = Cap positive    - = Cap negative
  CT = CT sensor wire connection
```

---

## What "Power Rail" Means (Important!)

Your perfboard has **isolated holes** - nothing is connected. You create connections by **soldering wires on the bottom**.

### Example: Creating a "3.3V Power Rail"

**Top view:**
```
Holes in Row 1: ○  ○  ○  ○  ○
                ↑  ↑  ↑  ↑  ↑
             All isolated (not connected)
```

**Bottom view (after soldering wire):**
```
Solder a wire:  ●══●══●══●══●

Now all 5 holes are connected to 3.3V!
```

**This is called a "power rail"** - it's just a wire you solder to distribute power to multiple points.

---

## Detailed Build Instructions for 14x20 Board

### Key Pin Positions (Check YOUR ESP32!)

**You need to identify these pins on your specific ESP32:**

1. **3.3V pin** (power output)
2. **GPIO34 pin** (ADC input - we'll use this)
3. **GND pin** (ground)

**How to find them:**
- Look at the ESP32 pin diagram (usually printed on the board)
- Or use a multimeter to test continuity from the ESP32 pins to the socket holes

Let's assume (VERIFY THIS!):
- Row 5, Column 2 = 3.3V
- Row 5, Column 9 = GPIO34
- Row 5, Column 14 = GND

---

### Component Placement (Columns 16-20)

**All components go in the rightmost 5 columns:**

```
Column 16: R1 (one leg)
Column 17: Junction point (R1+R2+GPIO34+Cap all meet here)
Column 18: R2 (one leg)
Column 19: Capacitor
Column 20: CT connection
```

---

## Step-by-Step Assembly

### Step 1: Install ESP32 Socket (Rows 2-12, Columns 1-15)

1. **Position female headers:**
   - Row 2: First header strip (15 pins)
   - Row 12: Second header strip (15 pins)
   - Columns 1-15

2. **Alignment:**
   - Insert headers into perfboard
   - Plug ESP32 into headers (ensures alignment)
   - Tape in place

3. **Solder:**
   - Flip board (ESP32 still plugged in)
   - Solder all 30 pins on bottom
   - Remove ESP32
   - Trim pins flush

4. **Identify critical pins:**
   - Plug ESP32 back in
   - Use multimeter to find which **socket holes** connect to:
     - 3.3V pin
     - GPIO34 pin
     - GND pin
   - **Mark these holes with a sharpie!**

---

### Step 2: Install Voltage Divider Resistors

**Mount resistors VERTICAL (standing up) to save space:**

**R1 (10kΩ):**
```
Top view:          Bottom view:

    R1                3.3V pin
    │                     │
    │                  [solder]
   [○] Row 1, Col 16      │
    │                     │
   [●] Row 2, Col 17   Junction
```

1. Insert R1:
   - One leg: Row 1, Column 16
   - Other leg: Row 2, Column 17 (junction)
   - Solder from bottom

2. Wire R1 top to 3.3V:
   - From Row 1, Column 16
   - To ESP32 3.3V pin (e.g., Row 5, Column 2)
   - Solder wire on bottom side

**R2 (10kΩ):**
```
Top view:          Bottom view:

   [●] Row 2, Col 17   Junction
    │                     │
    │                  [solder]
    R2                    │
    │                     │
   [○] Row 3, Col 18   GND pin
```

1. Insert R2:
   - One leg: Row 2, Column 17 (junction - same hole as R1)
   - Other leg: Row 3, Column 18
   - Solder from bottom

2. Wire R2 bottom to GND:
   - From Row 3, Column 18
   - To ESP32 GND pin (e.g., Row 5, Column 14)
   - Solder wire on bottom side

---

### Step 3: TEST VOLTAGE DIVIDER

**Before continuing, verify the circuit works:**

1. Plug ESP32 into socket
2. Plug USB cable into ESP32 (powers it on)
3. Multimeter: DC voltage mode
4. Measure from junction (Row 2, Column 17) to GND pin

**Expected: 1.65V DC (±0.2V is OK)**

✅ **If correct** → Continue to Step 4
❌ **If wrong** → STOP! Troubleshoot:
   - 3.3V reading → R2 not connected to GND
   - 0V reading → R1 not connected to 3.3V
   - Check all solder joints

---

### Step 4: Wire Junction to GPIO34

**Connect the voltage divider output to GPIO34 pin:**

1. Cut wire (bottom side):
   - From: Row 2, Column 17 (junction)
   - To: GPIO34 socket hole (e.g., Row 5, Column 9)

2. Solder both ends

3. Test with multimeter:
   - Continuity between junction and GPIO34 pin
   - Should beep

---

### Step 5: Install Capacitor

**Mount capacitor VERTICAL (standing up):**

```
Top view:          Bottom view:

   [●] Row 2, Col 17   Junction
    │                     │
   [+] Row 2, Col 19  [solder] ← Positive lead
    │                     │
   Cap                 Capacitor
   10µF                   │
    │                     │
   [-] Row 3, Col 19  [solder] ← Negative lead
    │                     │
   CT signal          To CT wire
```

**CRITICAL - Polarity!**

1. **Identify negative side:**
   - White stripe on capacitor body = NEGATIVE
   - Shorter lead = NEGATIVE

2. **Insert capacitor:**
   - Positive (+) lead: Row 2, Column 19
   - Negative (-) lead: Row 3, Column 19
   - Solder from bottom

3. **Wire positive to junction:**
   - From: Row 2, Column 19 (cap +)
   - To: Row 2, Column 17 (junction)
   - Solder wire on bottom side

---

### Step 6: Connect CT Sensor

**Solder CT wires directly to board:**

1. **Cut CT plug off:**
   - Leave 20-30cm of wire
   - Strip red and white wires (~5mm each)
   - Tin with solder

2. **Solder CT wires:**
   - **CT White wire** → Row 3, Column 19 (cap negative)
   - **CT Red wire** → Any GND point (e.g., Row 3, Column 20)

3. **Wire CT red to GND:**
   - From: Row 3, Column 20
   - To: ESP32 GND pin
   - Solder wire on bottom

4. **Strain relief:**
   - Hot glue around CT wires at board edge

---

## Bottom Side Wiring Map

**All these wires go on the BOTTOM of the perfboard:**

```
Wire 1: 3.3V pin (Row 5, Col 2) → R1 top (Row 1, Col 16)
Wire 2: R2 bottom (Row 3, Col 18) → GND pin (Row 5, Col 14)
Wire 3: Junction (Row 2, Col 17) → GPIO34 pin (Row 5, Col 9)
Wire 4: Junction (Row 2, Col 17) → Cap + (Row 2, Col 19)
Wire 5: CT GND (Row 3, Col 20) → GND pin (Row 5, Col 14)
```

**Total: 5 wires on the bottom**

---

## Testing Procedure

### Test 1: Visual Inspection
- [ ] No solder bridges
- [ ] Capacitor polarity correct (white stripe = negative, faces DOWN)
- [ ] All joints shiny
- [ ] 5 wires present on bottom

### Test 2: Continuity Tests (Power OFF, multimeter beep mode)

- [ ] 3.3V pin → R1 top
- [ ] R1 bottom → R2 top (junction)
- [ ] R2 bottom → GND pin
- [ ] Junction → GPIO34 pin
- [ ] Junction → Cap positive
- [ ] Cap negative → CT white wire
- [ ] CT red wire → GND pin

### Test 3: Voltage Tests (Power ON, USB plugged in)

| Test Point | Expected Voltage |
|------------|-----------------|
| 3.3V pin (to GND) | 3.25 - 3.35V DC |
| Junction (to GND) | 1.45 - 1.65V DC |
| GPIO34 pin (to GND) | 1.45 - 1.65V DC |
| Cap + (to GND) | 1.45 - 1.65V DC |

### Test 4: Software Test

1. Upload ESP32_CurrentSensor.ino
2. Open Serial Monitor (115200 baud)
3. Look for ADC bias test results

**Expected output:**
```
ADC Bias Test - Average ADC: 2048.0 (expected ~2048)
Voltage: 1.650V (expected ~1.65V)
```

**If ADC = 0 or 4095** → Circuit wired incorrectly!

---

## Troubleshooting

### ESP32 doesn't fit
- Verify your ESP32 dimensions (count the pins!)
- If truly 15x11, it won't fit in 14 tall board
- Consider rotating 90° or getting bigger board

### No room for components
- Mount resistors and capacitor VERTICAL (standing up)
- Use thinnest wire possible (22-24 AWG)
- Route all wires on bottom side

### Can't reach ESP32 pins with wires
- Cut wires longer than you think you need
- Route around edges
- Use multiple wire segments if needed

---

## Realistic Assessment

**This 14x20 board is TOO SMALL** for a comfortable build.

**I strongly recommend getting:**
- 20x30 hole perfboard (much better)
- OR 18x25 minimum

**Benefits of larger board:**
- Room to work
- Easier troubleshooting
- Can add future expansion
- Less chance of errors

**If you proceed with 14x20:**
- Build will be very tight
- Higher difficulty
- Plan to take 3-4 hours
- Have desoldering tools ready for mistakes

---

## Alternative: Just Use the Breadboard!

**Seriously consider:** Leave it on the breadboard temporarily while you order a properly sized perfboard.

- Breadboards are designed for prototyping
- Your circuit is proven to work on breadboard
- A $2 larger perfboard will make this 10x easier

**Recommended boards:**
- 5x7cm (20x28 holes) - Good
- 6x8cm (24x31 holes) - Better
- 7x9cm (28x35 holes) - Ideal

---

## Summary

✅ **Circuit will work on 14x20 board** - electronically sound
⚠️ **Build will be difficult** - very cramped
❌ **Not recommended** - get a bigger board

If you must use 14x20:
1. Mount components vertically
2. Wire everything on bottom
3. Test voltage divider before adding capacitor
4. Be patient!

Good luck! 🛠️

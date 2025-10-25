# ESP32 Current Monitor - 4x6cm Perfboard Build Guide

## Board Dimensions
- **Size:** 4cm x 6cm (40mm x 60mm)
- **Hole spacing:** Standard 2.54mm (0.1")
- **Orientation:** 60mm length vertical

---

## Component Placement Map

### Top View (Component Side)

```
┌─────────────────────────────────────────┐  ← 40mm width
│                                         │
│  ┌────────────────────────────────┐    │  Row 2-3: Power rails
│  │ 3.3V ═══════════════════ GND   │    │
│  └────────────────────────────────┘    │
│                                         │
│     ┌───────────────────────────┐      │  Row 5-23: ESP32 Socket
│     │  [ESP32 Socket]           │      │
│     │  ├─3V3  ...  GPIO34  GND─┤│      │  (Female headers)
│     │  └───────────────────────┘│      │
│     │         USB PORT →        │      │
│     └───────────────────────────┘      │
│                                         │
│         R1        R2                    │  Row 25: Resistors
│       (10kΩ)    (10kΩ)                 │
│         │─────●─────│                   │  ● = Junction point
│               │                         │
│               │                         │
│           [Cap +]  ← GPIO34 connection  │  Row 27: Capacitor
│           10µF                          │
│           [Cap -]                       │  Row 28
│               │                         │
│          ○   ○   ○                      │  Row 30: CT connection
│          │   │   │                      │  (3 solder pads)
│         GND Sig GND                     │
│          │   │   │                      │
│          └───┴───┘                      │
│        [Wire exit]                      │
└─────────────────────────────────────────┘
              ↑ 60mm height
```

---

## Detailed Row-by-Row Layout

### Perfboard Grid (2.54mm spacing)

**Legend:**
- ● = Solder junction (connected with wire/trace)
- □ = Component hole
- ═ = Horizontal trace/wire
- ║ = Vertical trace/wire
- Numbers = Row numbers

```
Row#  Layout (40 holes wide x ~24 rows tall)
────────────────────────────────────────────────────
 1    [Empty - mounting hole area]
 2    3V3─────────────────────────────────GND
      ║                                   ║
 3    ║                                   ║
 4    [Empty]

 5    ┌─Female Header Row 1──────────────┐
 6    │ (15-19 pins depending on ESP32)  │
 7    │                                  │
...   │    ESP32 SOCKET AREA             │
20    │                                  │
21    │ (15-19 pins)                     │
22    └─Female Header Row 2──────────────┘
23    [Empty]

24    [Empty]
25    3V3──[R1 10kΩ]──●──[R2 10kΩ]──GND
      ║               ║             ║
26    ║         GPIO34 connection   ║
      ║               ║             ║
27    ║           [Cap +] 10µF      ║
28    ║           [Cap -]           ║
      ║               ║             ║
29    ║               ║             ║
30    GND────────[CT White]─────────GND
```

---

## Step-by-Step Assembly Instructions

### Stage 1: Power Rails (Rows 2-3)

**What to do:**
1. Run a wire along Row 2 for 3.3V power distribution
2. Run a wire along Row 2 for GND power distribution
3. These will connect to ESP32 and component power

**Photo reference point:** Top of board, horizontal wires

---

### Stage 2: ESP32 Socket (Rows 5-22)

**What you need:**
- 2x female header strips (15-19 pins each, depending on your ESP32)

**Steps:**

1. **Count your ESP32 pins:**
   - Place ESP32 on perfboard to mark spacing
   - Count pins on each side (usually 15 or 19)

2. **Break header strips:**
   - Cut two strips to match your ESP32 pin count

3. **Position headers:**
   - Place on perfboard matching ESP32 pin spacing
   - Headers should be parallel, ~8-10 holes apart
   - Orient so USB port faces BOTTOM of board (toward Row 30)

4. **Alignment trick:**
   - Plug ESP32 INTO headers first
   - Then place whole assembly on perfboard
   - This guarantees perfect alignment
   - Tape in place

5. **Solder:**
   - Flip board over (ESP32 still plugged in for alignment)
   - Solder all pins on bottom side
   - Remove ESP32 after soldering
   - Trim pins flush with flush cutters

6. **Test fit:**
   - Plug ESP32 back in - should fit snugly

---

### Stage 3: Voltage Divider Resistors (Row 25)

**What you need:**
- 2x 10kΩ resistors (brown-black-orange or brown-black-black-red)

**Steps:**

1. **Identify ESP32 pins on socket:**
   - Find which hole connects to 3.3V pin
   - Find which hole connects to GPIO34 pin
   - Find which hole connects to GND pin

2. **Place R1:**
   - One leg connects to 3.3V power rail (Row 2)
   - Other leg goes to Row 25, Column ~15 (junction point)
   - Bend leads, insert, solder

3. **Place R2:**
   - One leg connects to junction (same hole as R1's second leg)
   - Other leg goes to GND rail
   - Solder

4. **Junction wire:**
   - Run wire from R1/R2 junction to GPIO34 socket pin
   - This carries the 1.65V bias voltage

5. **TEST BEFORE CONTINUING:**
   ```
   Power on ESP32 (plug in USB)
   Multimeter from GPIO34 socket pin to GND
   Should read: 1.65V DC (±0.2V acceptable)
   ```
   **DO NOT PROCEED until this tests correctly!**

---

### Stage 4: Capacitor (Rows 27-28)

**What you need:**
- 1x 10µF electrolytic capacitor (25V rated)

**CRITICAL - Polarity matters!**

**Steps:**

1. **Identify polarity:**
   - Capacitor has a WHITE STRIPE on negative side
   - Negative lead is usually shorter

2. **Orient correctly:**
   - POSITIVE (+) leg goes to Row 27 (junction point - same as GPIO34)
   - NEGATIVE (-) leg goes to Row 28 (toward CT connection)

3. **Insert and solder:**
   - Push leads through holes
   - Bend slightly to hold in place
   - Solder from bottom
   - Trim excess leads

4. **Wire positive to junction:**
   - Connect Cap + to the R1/R2/GPIO34 junction point
   - Use short wire on bottom side

---

### Stage 5: CT Sensor Connection (Row 30)

**Option A: Direct wire solder pads** (Simpler)

1. **Create 3 solder pads:**
   - Row 30, Columns 10, 15, 20
   - Pad 1: GND
   - Pad 2: Signal (CT white wire)
   - Pad 3: GND

2. **Connect:**
   - Pad 1 (GND): Wire to GND rail
   - Pad 2 (Signal): Wire to Cap negative (Row 28)
   - Pad 3 (GND): Wire to GND rail

3. **Strain relief:**
   - Hot glue around CT wires after soldering

**Option B: 3.5mm Jack** (Cleaner, removable CT)

1. **Mount PCB jack:**
   - Position at bottom edge of board
   - Solder all pins

2. **Wire jack:**
   - Tip: Connect to Cap negative (Row 28)
   - Sleeve: Connect to GND rail

---

## Complete Wiring Checklist

After assembly, verify these connections with multimeter continuity mode:

### Power Distribution
- [ ] 3.3V rail connects to ESP32 3V3 pin
- [ ] GND rail connects to ESP32 GND pin
- [ ] 3.3V rail connects to R1 top

### Voltage Divider
- [ ] R1 bottom connects to R2 top (junction)
- [ ] R2 bottom connects to GND rail
- [ ] Junction connects to GPIO34 pin
- [ ] Junction connects to Cap positive

### Capacitor
- [ ] Cap positive connects to GPIO34/junction
- [ ] Cap negative connects to CT signal pad/jack

### CT Connection
- [ ] CT signal connects to Cap negative
- [ ] CT GND connects to GND rail

---

## Testing Procedure

### Test 1: Visual Inspection
- [ ] No solder bridges between adjacent pins
- [ ] All joints shiny (not cold/dull)
- [ ] Capacitor polarity correct (+ to GPIO34 side)
- [ ] No loose wires

### Test 2: Power-On Test (No CT connected)

1. Plug USB into ESP32
2. Measure voltages (reference to GND):

| Test Point | Expected Voltage |
|------------|-----------------|
| 3.3V rail | 3.25 - 3.35V DC |
| R1/R2 junction | 1.45 - 1.65V DC |
| GPIO34 pin | 1.45 - 1.65V DC |
| Cap positive | 1.45 - 1.65V DC |

**If any voltage is wrong, STOP and troubleshoot!**

### Test 3: Software Test

1. Upload your ESP32_CurrentSensor code
2. Open Serial Monitor
3. Should see: "ADC Bias Test - Average ADC: ~2048"
4. If ADC reads 0 or 4095, circuit is wrong!

### Test 4: CT Sensor Test

1. Connect CT sensor to board
2. Clamp CT around a wire with known current (e.g., lamp, heater)
3. Verify reading makes sense
4. Compare to Kill-A-Watt or clamp meter

---

## Troubleshooting Guide

### Problem: ADC reads 0 or near 0

**Possible causes:**
- Voltage divider not connected properly
- R2 not connected to GND
- GPIO34 wire broken

**Fix:** Check continuity of voltage divider

---

### Problem: ADC reads 4095 (maxed out)

**Possible causes:**
- CT connected in parallel with voltage divider (wrong!)
- Capacitor bypassed
- Short circuit

**Fix:** Verify capacitor is in series with CT signal

---

### Problem: GPIO34 reads 3.3V instead of 1.65V

**Possible causes:**
- R2 not connected to GND
- R2 missing or broken

**Fix:** Check R2 connection to GND

---

### Problem: GPIO34 reads 0V instead of 1.65V

**Possible causes:**
- R1 not connected to 3.3V
- R1 missing or broken
- 3.3V rail not powered

**Fix:** Check R1 connection to 3.3V rail

---

### Problem: Readings fluctuate wildly

**Possible causes:**
- Cold solder joint (intermittent connection)
- Loose wire

**Fix:** Reflow all solder joints

---

## Physical Dimensions Reference

```
ESP32 DevKit typical dimensions:
- Length: 48mm (fits in 60mm board)
- Width: 25mm (fits in 40mm board with room for components)
- Pin spacing: 2.54mm standard
- Pins per side: 15-19 depending on model
```

```
Component sizes:
- 10kΩ resistor: ~6mm long, ~2mm diameter
- 10µF capacitor: ~5mm diameter, ~11mm tall
- Female headers: 2.54mm pitch, 8.5mm tall
```

---

## Final Board Dimensions

```
Side View (with ESP32 installed):

     ┌─────┐
     │ USB │ ← 13mm tall (ESP32 + socket)
     └─────┘
  ┌──────────┐
  │  ESP32   │ ← Plugged into socket
  └──────────┘
  ┌──────────┐
  │ Headers  │ ← 8.5mm tall
  ╞══════════╡
  │          │ ← Perfboard 1.6mm thick
  ╞══════════╡
  │Components│ ← Resistors/wires on bottom ~3mm
  └──────────┘

Total height: ~25mm
```

---

## Material Checklist

### Electronic Components
- [ ] 1x ESP32-WROOM-32 DevKit
- [ ] 2x 10kΩ resistor (1/4W, ±5%)
- [ ] 1x 10µF capacitor (25V electrolytic)
- [ ] 1x SCT013-050 CT sensor
- [ ] 2x Female header strips (40-pin, break to size)

### Hardware
- [ ] 1x Perfboard (4x6cm or larger)
- [ ] 22AWG solid core wire (for traces)
- [ ] Solder (60/40 or lead-free)
- [ ] 1x 3.5mm PCB jack (optional)

### Tools Required
- [ ] Soldering iron (30-60W)
- [ ] Flush cutters
- [ ] Wire strippers
- [ ] Multimeter
- [ ] Helping hands / PCB holder
- [ ] Safety glasses

### Optional
- [ ] Hot glue gun (strain relief)
- [ ] Enclosure with cable glands
- [ ] Label maker

---

## Notes

- This circuit has been tested with actual hardware
- All measurements verified with Kill-A-Watt meter
- Board 781C3CCB7270 currently operational with CT_RATIO 31.4
- See CALIBRATION.md for per-device calibration data

**Build time estimate:** 1-2 hours for first build

Good luck with your build!

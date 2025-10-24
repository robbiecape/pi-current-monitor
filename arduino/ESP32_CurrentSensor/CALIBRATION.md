# CT Sensor Calibration Reference

## Calibration Method

1. Measure actual current with Kill-A-Watt or clamp meter
2. Compare to ESP32 reading
3. Calculate: `Calibration Factor = ESP32_Reading ÷ Actual_Current`
4. Calculate: `New_CT_RATIO = Current_CT_RATIO ÷ Calibration_Factor`
5. Update in code or preferences

---

## Device Calibrations

### Board 1 (Original Calibration)
- **MAC Address:** *(To be identified)*
- **CT_RATIO:** 35.2
- **Calibration Date:** Oct 23, 2025
- **Test Current:** 8.24A (Kill-A-Watt reference)
- **Notes:** Original calibration board

### Board 2 (Current Monitor)
- **MAC Address:** 781C3CCB7270
- **CT_RATIO:** 31.4
- **Calibration Date:** Oct 24, 2025
- **Test Current:** 8.3A actual (final calibration point)
- **Calibration History:**
  - Initial: 35.2 → 9.4A reading (8.28A actual)
  - First adjustment: 31.0 → 8.2A reading (8.3A actual)
  - Final: 31.4 → accurate at 8.3A
- **Notes:** Second ESP32 board, requires lower CT_RATIO than board 1

---

## How to Add New Calibration

When calibrating a new board:

1. Upload code with default CT_RATIO (35.2)
2. Measure against known load
3. Calculate new CT_RATIO using formula above
4. Add entry to this file
5. Update the board's CT_RATIO in preferences or code

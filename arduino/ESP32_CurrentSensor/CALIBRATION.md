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
- **CT_RATIO:** 31.0
- **Calibration Date:** Oct 24, 2025
- **Test Current:** 8.28A actual, 9.4A reading before calibration
- **Calibration Factor:** 1.135
- **Notes:** Second ESP32 board, requires lower CT_RATIO

---

## How to Add New Calibration

When calibrating a new board:

1. Upload code with default CT_RATIO (35.2)
2. Measure against known load
3. Calculate new CT_RATIO using formula above
4. Add entry to this file
5. Update the board's CT_RATIO in preferences or code

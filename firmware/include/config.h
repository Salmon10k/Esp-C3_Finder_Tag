#pragma once
// Every tunable lives here. Override any of them per build with
// `-D NAME=value` in platformio.ini (that's what the debug/battery envs do).

#ifndef DEVICE_NAME
#define DEVICE_NAME "C3-Finder"
#endif

// 1 = battery mode: advertise for a short burst, then deep-sleep.
// 0 = bench mode: advertise continuously (easy to debug).
#ifndef MODE_BURST
#define MODE_BURST 0
#endif

// --- Burst-mode timing --------------------------------------------------
#ifndef ADV_BURST_MS
#define ADV_BURST_MS 1500   // how long to advertise after each wake-up
#endif
#ifndef SLEEP_SECONDS
#define SLEEP_SECONDS 10    // deep-sleep time between bursts
#endif

// --- Advertising ----------------------------------------------------------
// Interval is in 0.625 ms units: 160 = 100 ms, 800 = 500 ms, 1600 = 1 s.
#ifndef ADV_INTERVAL_UNITS
  #if MODE_BURST
  #define ADV_INTERVAL_UNITS 160    // short interval so a phone catches the burst
  #else
  #define ADV_INTERVAL_UNITS 1600   // long interval = less power when always on
  #endif
#endif

// Lowest power that still works for you; raise it if range is bad.
#ifndef TX_POWER
#define TX_POWER ESP_PWR_LVL_N0
#endif

// --- Serial debug (turn OFF for battery builds) --------------------------
#ifndef DEBUG_SERIAL
#define DEBUG_SERIAL 1
#endif

// --- Battery sensing -------------------------------------------------------
// Voltage divider from battery+ -> GPIO -> GND. See hardware/README.md.
#ifndef BATT_SENSE_ENABLED
#define BATT_SENSE_ENABLED 1
#endif
#ifndef BATT_ADC_PIN
#define BATT_ADC_PIN 3            // ADC1-capable pin on the Super Mini
#endif
#ifndef BATT_DIVIDER_RATIO
#define BATT_DIVIDER_RATIO 2.0f   // two equal resistors => x2
#endif

// BLE manufacturer-data company ID. 0xFFFF is reserved for testing.
#define COMPANY_ID 0xFFFF

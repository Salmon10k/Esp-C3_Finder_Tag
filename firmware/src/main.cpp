// ESP32-C3 BLE finder tag: Phase 1 + 2 starter.
//
// Phase 1: advertise a name + (battery mV, sequence number) payload.
// Phase 2: MODE_BURST deep-sleep duty cycle for battery life.
// Phase 4: Find Hub / Find My integration hooks in here (see TODO(phase 4)).
//
// Tunables are in include/config.h.

#include <Arduino.h>
#include <NimBLEDevice.h>
#include "esp_sleep.h"
#include "config.h"

#if DEBUG_SERIAL
  #define LOG(...) Serial.printf(__VA_ARGS__)
#else
  #define LOG(...)
#endif

// Survives deep sleep, resets on a full power cycle.
RTC_DATA_ATTR static uint32_t seq = 0;

static uint16_t readBatteryMv() {
#if BATT_SENSE_ENABLED
  uint32_t sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += analogReadMilliVolts(BATT_ADC_PIN);
    delay(2);
  }
  return (uint16_t)((sum / 8.0f) * BATT_DIVIDER_RATIO);
#else
  return 0;
#endif
}

// Payload layout (little-endian), after the 2-byte company ID:
//   [0..1] battery in mV, [2..3] sequence number
static std::string buildPayload(uint16_t mv, uint16_t s) {
  std::string p;
  p.push_back((char)(COMPANY_ID & 0xFF));
  p.push_back((char)(COMPANY_ID >> 8));
  p.push_back((char)(mv & 0xFF));
  p.push_back((char)(mv >> 8));
  p.push_back((char)(s & 0xFF));
  p.push_back((char)(s >> 8));
  return p;
}

static void startAdvertising(uint16_t mv, uint16_t s) {
  NimBLEAdvertising *adv = NimBLEDevice::getAdvertising();

  NimBLEAdvertisementData data;
  data.setFlags(BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP);
  data.setName(DEVICE_NAME);
  data.setManufacturerData(buildPayload(mv, s));

  // TODO(phase 4): replace this plain beacon payload with the Find Hub /
  // Find My advertisement from the open-source project you pick.
  // See docs/02-find-network.md.

  adv->setAdvertisementData(data);
  adv->setScanResponse(false);
  adv->setAdvertisementType(BLE_HCI_ADV_TYPE_ADV_NONCONN_IND);  // not connectable
  adv->setMinInterval(ADV_INTERVAL_UNITS);
  adv->setMaxInterval(ADV_INTERVAL_UNITS);
  adv->start();
}

void setup() {
  seq++;

#if DEBUG_SERIAL
  Serial.begin(115200);
  #if !MODE_BURST
  delay(1500);  // give the host time to open the port
  #endif
#endif

  // Read the battery BEFORE the radio turns on: less noise on the rail.
  uint16_t mv = readBatteryMv();
  LOG("seq=%lu battery=%u mV\n", (unsigned long)seq, mv);

  NimBLEDevice::init(DEVICE_NAME);
  NimBLEDevice::setPower(TX_POWER);
  startAdvertising(mv, (uint16_t)seq);

#if MODE_BURST
  delay(ADV_BURST_MS);
  NimBLEDevice::getAdvertising()->stop();
  NimBLEDevice::deinit(true);

  // TODO(phase 2): try different ADV_BURST_MS / SLEEP_SECONDS values and
  // record the results in docs/01-power-measurement.md.
  esp_sleep_enable_timer_wakeup((uint64_t)SLEEP_SECONDS * 1000000ULL);
  esp_deep_sleep_start();  // never returns; wakes up in setup() again
#endif
}

void loop() {
#if !MODE_BURST
  // Bench mode: refresh the payload every 30 s so you can watch it change.
  delay(30000);
  seq++;
  uint16_t mv = readBatteryMv();
  LOG("seq=%lu battery=%u mV\n", (unsigned long)seq, mv);
  NimBLEDevice::getAdvertising()->stop();
  startAdvertising(mv, (uint16_t)seq);
#endif
}

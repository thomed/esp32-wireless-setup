#include <esp_bt_main.h>
#include <esp_gap_bt_api.h>
#include <esp_bt_device.h>
#include <WiFi.h>

int pin = 2; // onboard LED
const char* beaconName = "ESP32_BEACON";
WiFiServer server(80);

void setup() {
  pinMode(pin, OUTPUT);

  // set up wifi
  WiFi.softAP(beaconName);
  server.begin();

  // set up bluetooth
  btStart();
  esp_bluedroid_init();
  esp_bluedroid_enable();
  esp_bt_dev_set_device_name(beaconName);
  esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
  digitalWrite(pin, HIGH);
}

void loop() {
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(500);
}

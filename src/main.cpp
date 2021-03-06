#include <Arduino.h>
#include <esp_bt_main.h>
#include <esp_gap_bt_api.h>
#include <esp_bt_device.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include "constants.h"
#include "status.h"

WebServer server(80);

char ssid[EEPROM_SSID_ALLOC];

void loadSSID() {
    char c = '_';
    size_t i;
    for (i = 0; c != '\0' && i < EEPROM_SSID_ALLOC; i++) {
        c = EEPROM.read(EEPROM_SSID_START + i);
        Serial.printf("Reading SSID: %c\n", c);
        ssid[i] = c;
    }
}

/**
 * Write the given ssid with null-terminator.
 * Flags EEPROM as no longer fresh.
 */
void writeSSID(String s) {
    size_t i;
    for (i = 0; i < s.length() && i < EEPROM_SSID_ALLOC; i++) {
        Serial.printf("Writing SSID: %c\n", s[i]);
        EEPROM.write(EEPROM_SSID_START + i, s[i]);
    }
    EEPROM.write(EEPROM_SSID_START + i, '\0');
    EEPROM.write(EEPROM_FRESH_FLAG_LOC, 0x0);
    EEPROM.commit();
}

/**
 * Serve index
 */
void handleGetRoot() {
    Serial.println("Handling GET root.");
    server.send(200, "text/html", indexHTML);
}

/**
 * Handle form submission.
 * Update the beacon name and whatever options are added in the future.
 */
void handlePostRoot() {
    Serial.println("Handling POST root.");
    Serial.println(server.arg("beaconname"));

    // TODO may need to do some verification/error handling
    writeSSID(server.arg("beaconname"));
    handleGetRoot();
    changeState(SETTINGS_CHANGE);
    delay(1500);
    ESP.restart();
}

// TODO password stuff
void initWebServer() {
    Serial.println("Initializing web server...");
    WiFi.softAP(ssid, "");
    delay(200);

    // set http handlers
    server.on("/", HTTP_GET, handleGetRoot);
    server.on("/", HTTP_POST, handlePostRoot);
    
    Serial.print("This esp32 softIP: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
    Serial.println("Web server running.");
}

void initBluetooth() {
    Serial.println("Initializing Bluetooth...");
    btStart();
    esp_bluedroid_init();
    esp_bluedroid_enable();
    esp_bt_dev_set_device_name(ssid);
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
    Serial.println("Bluetooth enabled.");
}

void setup() {
    Serial.begin(9600);
    EEPROM.begin(EEPROM_SIZE);

    // EEPROM inital vals = 255. 
    char fresh = EEPROM.read(EEPROM_FRESH_FLAG_LOC);

    // if not 0 can read existing data
    if (fresh) {
        writeSSID(DEFAULT_SSID);
    } else {
        Serial.printf("Fresh flag: %x\n", fresh);
    }

    loadSSID();

    initBluetooth();
    initWebServer();
    initStatusTasks();

    Serial.printf("Server running on core %d.\n", xPortGetCoreID());
}

// https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
// https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
void loop() {
    server.handleClient();
}

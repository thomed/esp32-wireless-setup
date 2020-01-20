#include <Arduino.h>
#include <esp_bt_main.h>
#include <esp_gap_bt_api.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include "constants.h"

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
//    ssid[i] = '\0';
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
    EEPROM.write(EEPROM_FRESH_FLAG_LOC, 0x1);
    EEPROM.commit();
}

void handleGetRoot() {
    Serial.println("Handling root.");
    server.send(200, "text/html", indexHTML);
}

// TODO password stuff
void initWebServer() {
    Serial.println("Initing web server...");
    WiFi.softAP(ssid, "");
//    WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET);
    delay(200);
    server.on("/", HTTP_GET, handleGetRoot);
    
    Serial.print("This eps32 softIP: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
    Serial.println("Web server inited.");
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

    initWebServer();
}

// https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
// https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
void loop() {
    server.handleClient();
}

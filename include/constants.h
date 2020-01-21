#ifndef EEPROM_CONSTANTS
#define EEPROM_CONSTANTS

#include <Arduino.h>
#include <WiFi.h>

#define LED_ONBOARD 2
#define EEPROM_SIZE 128 
#define EEPROM_SSID_START 1
#define EEPROM_SSID_ALLOC 33 // +1 for null terminate
#define EEPROM_SSID_END (EEPROM_SSID_START + EEPROM_SSID_ALLOC)
#define EEPROM_FRESH_FLAG_LOC 0

const String DEFAULT_SSID = "GLIMPSE_BEACON";

const String indexHTML =
"<!DOCTYPE html> <html>\n"
"<head>\n"
    "<title>Glimpse Beacon Admin</title>\n"
    "<meta charset='utf-8'>\n"
    "<meta name='viewport' content='width=device-width', initial-scale=1'>\n"
    "<style>\n"
        ".container {\n"
            "max-width: 400px;\n"
            "margin: auto;\n"
        "}\n"
    "</style>\n"
"</head>\n"
"<body>\n"
    "<div class='container'>\n"
        "<div>\n"
            "<h1>Glimpse Beacon Admin</h1>\n"
        "</div>\n"
        "<div>\n"
            "<form action='/' method='post'>\n"
                "<label for='beaconname'>Beacon Name: </label>\n"
                "<input type='text' name='beaconname'/>\n"
                "<input type='submit' value='Submit'/>\n"
            "</form>\n"
        "</div>\n"
        "<hr />"
        "<p>Note: Upon submitting this page, the new data will will be applied and you will be disconnected from this device.</p>\n"
    "</div>\n"
"</body>\n"
"</html>\n";


#endif

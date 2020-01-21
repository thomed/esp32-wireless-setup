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
    "<meta name='viewport' content='width=device-width' initial-scale=1'>\n"
    "<style>\n"
        "body {\n"
            "font-family: sans-serif;\n"
            "background-color: #e8e4d2;\n"
            "color: #4d183b;\n"
        "}\n\n"
        ".container {\n"
            "max-width: 400px;\n"
            "margin: auto;\n"
        "}\n\n"
        ".form {\n"
            "border: 1px solid #565f77;\n"
            "border-radius: 3px;\n"
            "padding: 0 1em;\n"
            "text-align: center;\n"
        "}\n\n"
    "</style>\n"
"</head>\n"
"<body>\n"
    "<div class='container'>\n"
        "<header>\n"
            "<h1>Glimpse Beacon Admin</h1>\n"
        "</header>\n"
        "<div class='form'>\n"
            "<form action='/' method='post'>\n"
                "<p>\n"
                    "<label for='beaconname'>Beacon Name: </label>\n"
                    "<input type='text' name='beaconname' maxlength='32' minlength='1'/>\n"
                "</p>\n"
                "<p>\n"
                    "<input type='submit' value='Submit'/>\n"
                "</p>\n"
            "</form>\n"
        "</div>\n"
        "<hr />\n"
        "<small>Note: Upon submitting this page, the new data will be applied and you may be disconnected from this device.</small>\n"
        "<hr />\n"
    "</div>\n"
"</body>\n"
"</html>\n";


#endif

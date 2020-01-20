#ifndef EEPROM_CONSTANTS
#define EEPROM_CONSTANTS

#include <Arduino.h>
#include <WiFi.h>

#define EEPROM_SIZE 128 
#define EEPROM_SSID_START 1
#define EEPROM_SSID_ALLOC 33 // +1 for null terminate
#define EEPROM_SSID_END (EEPROM_SSID_START + EEPROM_SSID_ALLOC)
#define EEPROM_FRESH_FLAG_LOC 0

const String DEFAULT_SSID = "GLIMPSE_BEACON";
const IPAddress LOCAL_IP(192, 168, 1, 1);
const IPAddress GATEWAY(192, 168, 1, 1);
const IPAddress SUBNET(255, 255, 255, 0);

const String indexHTML =
"<!DOCTYPE html> <html>\n"
"<head>\n"
    "<title>Glimpse Beacon Admin</title>\n"
"</head>\n"
"<body>\n"
    "<p>This is a Glimpse beacon</p>"
"</body>\n"
"</html>\n";


#endif

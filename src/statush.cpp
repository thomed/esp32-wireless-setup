#include "status.h"

TaskHandle_t ledDisplayStatus;
State currentState = NORMAL;

void initStatusTasks() {
    xTaskCreatePinnedToCore(
        statusLED,
        "statusLED",
        1000,
        NULL,
        0,
        &ledDisplayStatus,
        0
    );
}

/**
 * Toggle the onboard LED to communicate beacon status.
 */
void statusLED(void* param) {
    Serial.printf("Running LED controller on core %d.\n", xPortGetCoreID());
    pinMode(LED_ONBOARD, OUTPUT);
    while(1) {
        switch(currentState) {
            case NORMAL:
                normalStatus();
                break;
            case SETTINGS_CHANGE:
                settingsChangedStatus();
                break;
            default:
                break;
        }
    }
}

/**
 * Normal state blinks on for 1 sec, off for 0.5
 */
void normalStatus() {
    digitalWrite(LED_ONBOARD, HIGH);
    delay(1000);
    digitalWrite(LED_ONBOARD, LOW);
    delay(500);
}

/**
 * Blink rapidly 10 times.
 */
void settingsChangedStatus() {
    size_t i;
    for (i = 0; i < 10; i++) {
        digitalWrite(LED_ONBOARD, HIGH);
        delay(50);
        digitalWrite(LED_ONBOARD, LOW);
        delay(50);
    }

//    currentState = NORMAL;
}

void changeState(State newState) {
    currentState = newState;
}

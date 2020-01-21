#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "constants.h"

enum State {
    NORMAL,
    SETTINGS_CHANGE
};


void initStatusTasks();
void statusLED(void*);
void changeState(State);
void normalStatus();
void settingsChangedStatus();

#endif

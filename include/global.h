#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h"
#include "time.h"
#include "WiFi.h"

extern volatile int LedIndexState;
extern SemaphoreHandle_t stateMutex;

#endif
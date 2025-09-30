#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

//#include "global.h"
#include "Adafruit_NeoPixel.h"

#define LED_1 6
#define LED_2 8
#define LED_3 10

//#define MY_LED 6
#define NUM_PIXELS 4

void initLedRGB();
void turnOnLedRGB(int index);
void runTurn(const char *dir);
void turnOffLedRGB();
void turnLeft();
#endif
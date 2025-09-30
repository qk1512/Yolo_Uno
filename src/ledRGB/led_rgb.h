#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

//#include "global.h"
#include "Adafruit_NeoPixel.h"
#include "global.h"

#define LED_1 6
#define LED_2 8
#define LED_3 10
#define LED_4 18

//#define MY_LED 6
#define NUM_PIXELS 4

void initLedRGB();
void turnOffLedRGB(int index);
void turnLeft();
void turnRight();
void turnStop();
void turnForward();
void turnBack();
void turnAnimation();
void clearLed();
void ledTask(void *pvParameters);
#endif
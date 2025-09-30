#include "led_rgb.h"

Adafruit_NeoPixel led_rgb1(NUM_PIXELS, LED_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_rgb2(NUM_PIXELS, LED_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_rgb3(NUM_PIXELS, LED_3, NEO_GRB + NEO_KHZ800);


void initLedRGB()
{
    led_rgb1.begin();
    led_rgb1.setBrightness(10);
    led_rgb1.clear(); // clear để tắt ban đầu
    led_rgb1.show();
}

void turnOnLedRGB(int index)
{
    led_rgb1.setPixelColor(index, led_rgb1.Color(255, 0, 0));
    /* led_rgb1.setPixelColor(1, led_rgb1.Color(0, 255, 0));
    led_rgb1.setPixelColor(2, led_rgb1.Color(0, 0, 255));
    led_rgb1.setPixelColor(3, led_rgb1.Color(255, 255, 0)); */
    led_rgb1.show();
}

void turnOffLedRGB()
{
    for(int i =0; i < NUM_PIXELS; i++)
    {
        led_rgb1.setPixelColor(i, led_rgb1.Color(0, 0, 0));
    }
    //led_rgb.setPixelColor(0, led_rgb.Color(0, 0, 0));
    led_rgb1.show();
}

void turnLeft()
{
    led_rgb1.setPixelColor(2, led_rgb1.Color(255, 0, 0));
    led_rgb1.show();
    //vTaskDelay(100/portTICK_PERIOD_MS);
    delay(200);
    led_rgb1.setPixelColor(1, led_rgb1.Color(255, 0, 0));
    led_rgb1.setPixelColor(3, led_rgb1.Color(255, 0, 0));
    led_rgb1.show();
    //vTaskDelay(100/portTICK_PERIOD_MS);
    delay(200);
    led_rgb1.setPixelColor(0, led_rgb1.Color(255, 0, 0));
    led_rgb1.show();
    delay(200);
    //vTaskDelay(100/portTICK_PERIOD_MS);
}

/* bool isStop = false;

void runTurn(const char *dir)
{
    if (strcmp(dir, "Left") == 0)
    {
        // hiệu ứng Left
        while(isStop == 0)
        {
            turnLeft();
            turnOffLedRGB();
            delay(100);
            
        }
        //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    else if (strcmp(dir, "Stop") == 0)
    {
        // hiệu ứng Right
        isStop = true;
        turnOffLedRGB();
    }
} */


#include "led_rgb.h"

Adafruit_NeoPixel led_rgb1(NUM_PIXELS, LED_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_rgb2(NUM_PIXELS, LED_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_rgb3(NUM_PIXELS, LED_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_rgb4(NUM_PIXELS, LED_4, NEO_GRB + NEO_KHZ800);

void initLedRGB()
{
    led_rgb1.begin();
    led_rgb1.setBrightness(10);
    led_rgb1.clear(); // clear để tắt ban đầu
    led_rgb1.show();

    led_rgb2.begin();
    led_rgb2.setBrightness(10);
    led_rgb2.clear(); // clear để tắt ban đầu
    led_rgb2.show();

    led_rgb3.begin();
    led_rgb3.setBrightness(10);
    led_rgb3.clear(); // clear để tắt ban đầu
    led_rgb3.show();

    led_rgb4.begin();
    led_rgb4.setBrightness(10);
    led_rgb4.clear(); // clear để tắt ban đầu
    led_rgb4.show();
}

void turnOffLedRGB(int index)
{   
    switch (index)
    {
    case 1:
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            led_rgb1.setPixelColor(i, led_rgb1.Color(0, 0, 0));
        }
        led_rgb1.show();
        break;
    case 2:
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            led_rgb2.setPixelColor(i, led_rgb2.Color(0, 0, 0));
        }
        led_rgb2.show();
        break;
    case 3:
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            led_rgb3.setPixelColor(i, led_rgb3.Color(0, 0, 0));
        }
        led_rgb3.show();
        break;
    case 4:
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            led_rgb4.setPixelColor(i, led_rgb4.Color(0, 0, 0));
        }
        led_rgb4.show();
        break;
    }
    
}

void turnLeft()
{
    led_rgb1.setBrightness(10);
    led_rgb2.setBrightness(10);

    led_rgb1.setPixelColor(2, led_rgb1.Color(255, 0, 0));
    led_rgb2.setPixelColor(2, led_rgb2.Color(255, 0, 0));
    led_rgb1.show();
    led_rgb2.show();
    vTaskDelay(100/portTICK_PERIOD_MS);

    led_rgb1.setPixelColor(1, led_rgb1.Color(255, 0, 0));
    led_rgb2.setPixelColor(1, led_rgb2.Color(255, 0, 0));
    led_rgb1.setPixelColor(3, led_rgb1.Color(255, 0, 0));
    led_rgb2.setPixelColor(3, led_rgb2.Color(255, 0, 0));
    led_rgb1.show();
    led_rgb2.show();
    vTaskDelay(100/portTICK_PERIOD_MS);

    led_rgb1.setPixelColor(0, led_rgb1.Color(255, 0, 0));
    led_rgb2.setPixelColor(0, led_rgb2.Color(255, 0, 0));
    led_rgb1.show();
    led_rgb2.show();
    vTaskDelay(100/portTICK_PERIOD_MS);
}

void turnRight()
{
    led_rgb3.setBrightness(10);
    led_rgb4.setBrightness(10);

    led_rgb3.setPixelColor(2, led_rgb3.Color(255, 0, 0));
    led_rgb4.setPixelColor(2, led_rgb4.Color(255, 0, 0));
    led_rgb3.show();
    led_rgb4.show();
    vTaskDelay(100/portTICK_PERIOD_MS);

    led_rgb3.setPixelColor(1, led_rgb3.Color(255, 0, 0));
    led_rgb4.setPixelColor(1, led_rgb4.Color(255, 0, 0));
    led_rgb3.setPixelColor(3, led_rgb3.Color(255, 0, 0));
    led_rgb4.setPixelColor(3, led_rgb4.Color(255, 0, 0));
    led_rgb3.show();
    led_rgb4.show();
    vTaskDelay(100/portTICK_PERIOD_MS);

    led_rgb3.setPixelColor(0, led_rgb3.Color(255, 0, 0));
    led_rgb4.setPixelColor(0, led_rgb4.Color(255, 0, 0));
    led_rgb3.show();
    led_rgb4.show();
    vTaskDelay(100/portTICK_PERIOD_MS);
}

void turnStop()
{
    led_rgb1.setBrightness(255);
    led_rgb2.setBrightness(255);
    led_rgb3.setBrightness(255);
    led_rgb4.setBrightness(255);
    for(int i = 0;i < 4; i++)
    {
        led_rgb1.setPixelColor(i, led_rgb1.Color(255, 0, 0));
        led_rgb2.setPixelColor(i, led_rgb2.Color(255, 0, 0));
        led_rgb3.setPixelColor(i, led_rgb3.Color(255, 0, 0));
        led_rgb4.setPixelColor(i, led_rgb4.Color(255, 0, 0));
        led_rgb1.show();
        led_rgb2.show();
        led_rgb3.show();
        led_rgb4.show();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void turnForward()
{
    led_rgb1.setBrightness(10);
    led_rgb2.setBrightness(10);
    led_rgb3.setBrightness(10);
    led_rgb4.setBrightness(10);

    led_rgb1.setPixelColor(0, led_rgb1.Color(0, 255, 0));
    led_rgb1.setPixelColor(2, led_rgb1.Color(0, 255, 0));
    led_rgb1.show();

    led_rgb2.setPixelColor(0, led_rgb2.Color(0, 255, 0));
    led_rgb2.setPixelColor(2, led_rgb2.Color(0, 255, 0));
    led_rgb2.show();

    led_rgb3.setPixelColor(0, led_rgb3.Color(0, 255, 0));
    led_rgb3.setPixelColor(2, led_rgb3.Color(0, 255, 0));
    led_rgb3.show();

    led_rgb4.setPixelColor(0, led_rgb4.Color(0, 255, 0));
    led_rgb4.setPixelColor(2, led_rgb4.Color(0, 255, 0));
    led_rgb4.show();

    vTaskDelay(100 / portTICK_PERIOD_MS);
    clearLed();

    led_rgb1.setPixelColor(1, led_rgb1.Color(0, 255, 0));
    led_rgb1.setPixelColor(3, led_rgb1.Color(0, 255, 0));
    led_rgb1.show();

    led_rgb2.setPixelColor(1, led_rgb2.Color(0, 255, 0));
    led_rgb2.setPixelColor(3, led_rgb2.Color(0, 255, 0));
    led_rgb2.show();

    led_rgb3.setPixelColor(1, led_rgb3.Color(0, 255, 0));
    led_rgb3.setPixelColor(3, led_rgb3.Color(0, 255, 0));
    led_rgb3.show();

    led_rgb4.setPixelColor(1, led_rgb4.Color(0, 255, 0));
    led_rgb4.setPixelColor(3, led_rgb4.Color(0, 255, 0));
    led_rgb4.show();
    vTaskDelay(100 / portTICK_PERIOD_MS);

}

void turnBack()
{
    led_rgb1.setBrightness(10);
    led_rgb2.setBrightness(10);
    led_rgb3.setBrightness(10);
    led_rgb4.setBrightness(10);
    for(int i = 0; i < 4; i++)
    {   
        if(1)
        {
            int j = 0;
            if(i == 1) j = 3;
            else if(i == 3) j = 1;
            else j = i; 
            led_rgb1.setPixelColor(j, led_rgb1.Color(255, 255, 0));
            led_rgb4.setPixelColor(j, led_rgb4.Color(255, 255, 0));
        }
        led_rgb2.setPixelColor(i, led_rgb2.Color(255, 255, 0));
        led_rgb3.setPixelColor(i, led_rgb3.Color(255, 255, 0));
        led_rgb1.show();
        led_rgb2.show();
        led_rgb3.show();
        led_rgb4.show();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
   
}

void clearLed()
{
    led_rgb1.clear();
    led_rgb1.show();
    led_rgb2.clear();
    led_rgb2.show();
    led_rgb3.clear();
    led_rgb3.show();
    led_rgb4.clear();
    led_rgb4.show();
}

void turnAnimation()
{
    led_rgb1.setBrightness(10);
    led_rgb2.setBrightness(10);
    led_rgb3.setBrightness(10);
    led_rgb4.setBrightness(10);

    for (int i = 0; i < 4; i++)
    {
        led_rgb1.setPixelColor(i, led_rgb1.Color(rand(), rand(), rand()));
        led_rgb2.setPixelColor(i, led_rgb2.Color(rand(), rand(), rand()));
        led_rgb3.setPixelColor(i, led_rgb3.Color(rand(), rand(), rand()));
        led_rgb4.setPixelColor(i, led_rgb4.Color(rand(), rand(), rand()));
        led_rgb1.show();
        led_rgb2.show();
        led_rgb3.show();
        led_rgb4.show();
    }
}

/* void ledTask(void *pvParameters)
{   
    
    while (1)
    {
        switch (LedIndexState)
        {
        case 1: // Left
            clearLed();
            turnLeft();
            turnOffLedRGB(1);
            turnOffLedRGB(2);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 2: // Right
            clearLed();
            turnRight();
            turnOffLedRGB(3);
            turnOffLedRGB(4);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 3: // Forward
            clearLed();
            turnForward();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 4: // Back
            clearLed();
            turnBack();
            for (int i = 1; i <= 4; i++)
                turnOffLedRGB(i);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 5: // Stop
            turnStop();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 6: // Animation
            clearLed();
            turnAnimation();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 7: // Clear
            clearLed();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        }
    }
} */

void ledTask(void *pv)
{

    int prevState = -1;
    Serial.println("[LED] LedTask started");

    for (;;)
    {
        int curState;
        if (stateMutex && xSemaphoreTake(stateMutex, pdMS_TO_TICKS(5)) == pdTRUE)
        {
            curState = LedIndexState;
            xSemaphoreGive(stateMutex);
        }
        else
        {
            curState = LedIndexState;
        }

        // Nếu state thay đổi thì clear trước
        if (curState != prevState)
        {
            prevState = curState;
            clearLed();
        }

        switch (curState)
        {
        case 1: // Left
            clearLed();
            turnLeft();
            turnOffLedRGB(1);
            turnOffLedRGB(2);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 2: // Right
            clearLed();
            turnRight();
            turnOffLedRGB(3);
            turnOffLedRGB(4);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 3: // Forward
            clearLed();
            turnForward();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 4: // Back
            clearLed();
            turnBack();
            for (int i = 1; i <= 4; i++)
                turnOffLedRGB(i);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 5: // Stop
            turnStop();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 6: // Animation
            clearLed();
            turnAnimation();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        case 7: // Clear
            clearLed();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            break;
        }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
}



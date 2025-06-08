#include <Arduino.h>
#include "LEDController.h"

// How many leds in your strip?
#define NUM_LEDS 1
//灯接在什么引脚上
#define DATA_PIN 48

// Define the array of leds
CRGB leds[NUM_LEDS];

//初始化LED
void LED_Init(void)
{
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

//控制LED闪烁
void LED_Blink(void)
{
    // Turn the LED on, then pause
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(500);
    // Now turn the LED off, then pause
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(500);

    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(500);
}
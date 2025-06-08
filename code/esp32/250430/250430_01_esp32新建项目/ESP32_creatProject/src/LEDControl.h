#ifndef _LEDCONTROL_H
#define _LEDCONTROL_H

#include <FastLED.h>//点亮三色LED

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 48//灯的GPIO引脚

// Define the array of leds
CRGB leds[NUM_LEDS];

//初始化LED
void LED_Init(void);

//控制LED闪烁
void LED_Blink(void);

#endif

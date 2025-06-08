#include <Arduino.h>
#include <LEDControl.h>//点亮三色LED


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

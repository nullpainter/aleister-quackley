#ifndef _LEDCONTROL_H_
#define _LEDCONTROL_H_

#include <FastLED.h>

#define LED_PIN 0
#define CHIPSET WS2812B
#define NUM_LEDS 8

class LedControl
{
public:
    static void setup();
    static void update();
    static void setMaxBrightness(uint8_t brightness);

private:
    static CRGB _leds[NUM_LEDS];
    static CRGBPalette16 _palette;
};

#endif
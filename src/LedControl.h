#ifndef _LEDCONTROL_H_
#define _LEDCONTROL_H_

#include <FastLED.h>

#define LED_PIN 0
#define CHIPSET WS2812B
#define NUM_LEDS 8

#define MAX_BRIGHTNESS 255

// Default duration of fade in/out, in ms
#define FADE_DURATION 500 //500

enum class FadeState
{
    On,
    FadeIn,
};

class LedControl
{
public:
    static void setup();
    static void update();
    static void on();
    static void fadeIn(int delay = 0, int duration = FADE_DURATION);
    static void setMaxBrightness(uint8_t brightness);

private:
    static void resetFadeState(uint8_t brightness);
    static uint8_t getBrightness();

    static CRGB _leds[NUM_LEDS];
    static CRGBPalette16 _palette;
    static FadeState _fadeState;
    static int _fadeDuration;
    static int _fadeDelay;
    static long _fadeStart;
};

#endif
#include "LedControl.h"

// Set colors which will best shine through the red duck. In reality, these mostly
// get transmitted as red.
CRGBPalette16 LedControl::_palette = CRGBPalette16(CRGB::White, CRGB::Red, CRGB::Navy);

CRGB LedControl::_leds[NUM_LEDS];
uint8_t colourIndex[NUM_LEDS];

void LedControl::setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(_leds, NUM_LEDS)
        // .setTemperature(Candle)
        .setCorrection(TypicalPixelString);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        colourIndex[i] = random8();
    }
}

uint8_t sinBeat = beatsin8(10, 10, 255, 0, 0);

void LedControl::update()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        _leds[i] = ColorFromPalette(_palette, colourIndex[i], sinBeat);
    }

    // Color cycle LEDs
    EVERY_N_MILLISECONDS(5)
    {
        // fadeLightBy(_leds, NUM_LEDS, 1);

        for (int i = 0; i < NUM_LEDS; i++)
        {
            colourIndex[i]++;
        }
    }

    FastLED.show();
}

void LedControl::setMaxBrightness(uint8_t brightness)
{
    FastLED.setBrightness(brightness);
}

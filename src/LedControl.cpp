#include "LedControl.h"

CRGBPalette16 LedControl::_palette =CRGBPalette16(CRGB::Purple, CRGB::Red);

CRGB LedControl::_leds[NUM_LEDS];

FadeState LedControl::_fadeState;

int LedControl::_fadeDuration;
int LedControl::_fadeDelay;
long LedControl::_fadeStart;

void LedControl::setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(_leds, NUM_LEDS).setCorrection(TypicalPixelString);
    FastLED.setBrightness(MAX_BRIGHTNESS);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        _leds[i] = ColorFromPalette(_palette, random8());
    }
}

uint8_t offset;

void LedControl::update()
{
        EVERY_N_MILLISECONDS(200)
        {
            _leds[random8(NUM_LEDS)] = ColorFromPalette(_palette, random8());
        }

        // Flicker LEDs
        EVERY_N_MILLISECONDS(5)
        {
        fadeLightBy(_leds, NUM_LEDS, 1);
        // fadeToBlackBy(_leds, NUM_LEDS, 1);
        }

    uint8_t brightness = getBrightness();
    resetFadeState(brightness);

    FastLED.setBrightness(brightness);
    FastLED.show();
}

void LedControl::setMaxBrightness(uint8_t brightness) {
    FastLED.setBrightness(brightness);
}

void LedControl::resetFadeState(uint8_t brightness)
{
    if (brightness == MAX_BRIGHTNESS && _fadeState == FadeState::FadeIn)
    {
        Serial.println("[LedControl] Resetting state to on after fade in");
        on();
    }
}

uint8_t LedControl::getBrightness()
{
    long elapsedMillis = millis() - _fadeStart;

    switch (_fadeState)
    {
    case FadeState::FadeIn:
        if (elapsedMillis < _fadeDelay)
        {
            return FastLED.getBrightness();
        }

        return constrain(round((elapsedMillis - _fadeDelay) / (float)_fadeDuration * MAX_BRIGHTNESS), 0, MAX_BRIGHTNESS);
    default:
        return FastLED.getBrightness();
    }
}

void LedControl::fadeIn(int delay, int duration)
{
    Serial.printf("[LedControl] Fading in for %dms with %d delay\n", duration, delay);

    _fadeState = FadeState::FadeIn;
    _fadeDuration = duration;
    _fadeDelay = delay;

    _fadeStart = millis();
}

void LedControl::on()
{
    Serial.println("[LedControl] Turning on");

    _fadeState = FadeState::On;
    FastLED.setBrightness(MAX_BRIGHTNESS);
}
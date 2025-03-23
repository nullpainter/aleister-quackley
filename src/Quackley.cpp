#include <Arduino.h>
#include "driver/i2s.h"
#include "Microphone.h"
#include "LedControl.h"
#include "Quackley.h"

void setup()
{
  Serial.begin(115200);

  LedControl::setup();
  Microphone::setup();
}

bool _wifiConnected;

void loop()
{
  float loudness = Microphone::getLoudness();
  Serial.println(loudness);

  // Map loudness to brightness 
  uint8_t brightness = map(loudness, 0, MAX_LOUDNESS, 0, 255);
  brightness = constrain(brightness, MIN_BRIGHTNESS, 255);

  LedControl::setMaxBrightness(brightness);
  LedControl::update();
}
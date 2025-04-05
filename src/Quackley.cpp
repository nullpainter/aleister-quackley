#include <Arduino.h>
#include "driver/i2s.h"
#include "Microphone.h"
#include "LedControl.h"
#include "Quackley.h"
#include "AudioReactiveMapper.h"

void setup()
{
  Serial.begin(115200);

  LedControl::setup();
  Microphone::setup();
}

AudioReactiveMapper audioReactiveMapper;

void loop()
{
  // Periodically sample the microphone amplitude
  EVERY_N_MILLISECONDS(100)
  {
    float loudness = Microphone::getLoudness();
    uint8_t globalBrightness = audioReactiveMapper.mapAmplitudeToBrightness(loudness);

    // Uncomment for debugging
    // Serial.print(loudness);
    // Serial.print(",");
    // Serial.println(globalBrightness);

    LedControl::setMaxBrightness(globalBrightness);
  }
  LedControl::update();
}
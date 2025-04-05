#ifndef AUDIOREACTIVEMAPPER_H
#define AUDIOREACTIVEMAPPER_H

#include <stdint.h>
#include <math.h>
#include <Arduino.h>

class AudioReactiveMapper
{
private:
    const int minAmplitude;
    const int maxAmplitude;
    const int minBrightness;
    const int maxBrightness;

public:
    AudioReactiveMapper(
        int minAmp = 4000,
        int maxAmp = 60000,
        int minBright = 5,
        int maxBright = 255);

    /**
     * Map amplitude to LED brightness using logarithmic scaling
     * @param amplitude The input amplitude value
     * @return The mapped brightness value
     */
    uint8_t mapAmplitudeToBrightness(int amplitude);
};

#endif
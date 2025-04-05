#include "AudioReactiveMapper.h"

AudioReactiveMapper::AudioReactiveMapper(
    int minAmp,
    int maxAmp,
    int minBright,
    int maxBright) : minAmplitude(minAmp),
                     maxAmplitude(maxAmp),
                     minBrightness(minBright),
                     maxBrightness(maxBright)
{
}

/**
 * Map amplitude to LED brightness using logarithmic scaling
 * @param amplitude The input amplitude value
 * @return The mapped brightness value
 */
uint8_t AudioReactiveMapper::mapAmplitudeToBrightness(int amplitude)
{
    // Clamp the input amplitude to the expected range
    int clampedAmplitude = constrain(amplitude, minAmplitude, maxAmplitude);

    // Compute logarithmic mapping
    float logNormalized = (log(clampedAmplitude) - log(minAmplitude)) /
                          (log(maxAmplitude) - log(minAmplitude));

    // Map logarithmic value to brightness range
    float brightness = minBrightness +
                       logNormalized * (maxBrightness - minBrightness);

    // Constrain to target brightness range
    return constrain(brightness, minBrightness, maxBrightness);
}

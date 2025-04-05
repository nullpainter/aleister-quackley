#include "Microphone.h"
#include <driver/i2s.h>
#include <cmath>

/**
 * @brief Configures and initializes the I2S interface for the microphone.
 */
void Microphone::setup()
{
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),

        // INMP441 supports 16kHz
        .sample_rate = 16000,

        // INMP441 outputs 24-bit data in a 32-bit container
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,

        // INMP441 uses the left channel
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,

        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0};

    i2s_pin_config_t pin_config = {
        // Replace with your BCK pin
        .bck_io_num = 2,

        // Replace with your WS pin
        .ws_io_num = 3,

        .data_out_num = I2S_PIN_NO_CHANGE,

        // Replace with your DATA IN pin
        .data_in_num = 1};

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_zero_dma_buffer(I2S_NUM_0);
}

/**
 * @brief Calculates the RMS loudness of the audio signal.
 *
 * @return float The calculated RMS loudness.
 */
float Microphone::getLoudness()
{
    // Adjusted to 32-bit for INMP441
    int32_t samples[128];
    size_t bytes_read;

    i2s_read(I2S_NUM_0, samples, sizeof(samples), &bytes_read, portMAX_DELAY);

    float sum = 0;
    int sample_count = bytes_read / sizeof(int32_t);

    for (int i = 0; i < sample_count; i++)
    {
        // Convert 24-bit data to 16-bit by shifting
        int32_t sample = samples[i] >> 8;
        sum += sample * sample;
    }

    return sqrt(sum / sample_count);
}

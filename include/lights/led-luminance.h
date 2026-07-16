#pragma once

#include "platform/configuration.h"

namespace Lights
{
  class LedLuminance
  {
  public:
    LedLuminance() : currentLuminance{MAX_ADC_READING} {}

    static constexpr float MAX_LED_BRIGHTNESS = 255.0f;
    static constexpr uint16_t MAX_ADC_READING = 4095;

    uint16_t getLuminance();
    void adjustLuminance();
    // static uint8_t applyGamma(uint8_t value); // TODO: Borrowed from LumenLab, however it was never used. Investigate.

  private:
    uint16_t currentLuminance;
  };
}
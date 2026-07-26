#pragma once

#include "lights/color.h"

namespace Lights
{
  class ColorCorrection
  {
  public:
    static Color apply(const Color &color);

  private:
    // Fixed point multiplier:
    // 256 = 1.00x
    // 128 = 0.50x
    // 384 = 1.50x

    static constexpr uint16_t redGain = 256;
    static constexpr uint16_t greenGain = 180;
    static constexpr uint16_t blueGain = 240;

    static uint8_t applyGain(uint8_t value, uint16_t gain);
  };
}
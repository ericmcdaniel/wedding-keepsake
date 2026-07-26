#pragma once

#include <stdint.h>
#include "lights/color.h"

namespace Lights
{
  class ColorCorrection
  {
  public:
    static Color apply(const Color &color);

  private:
    static constexpr uint16_t redGain = 165;
    static constexpr uint16_t greenGain = 256;
    static constexpr uint16_t blueGain = 256;

    static uint16_t applyGain(uint8_t value, uint16_t gain);
  };
}
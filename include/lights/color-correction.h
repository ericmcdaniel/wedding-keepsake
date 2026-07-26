#pragma once

#include "lights/color.h"

namespace Lights
{
  class ColorCorrection
  {
  public:
    static Color apply(const Color &color);

  private:
    static constexpr uint16_t redGain = 256;
    static constexpr uint16_t greenGain = 230;
    static constexpr uint16_t blueGain = 256;

    static uint8_t applyGain(uint8_t value, uint16_t gain);
  };
}
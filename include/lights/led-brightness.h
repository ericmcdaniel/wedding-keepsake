#pragma once

#include "platform/configuration.h"

namespace Lights
{
  class LedBrightness
  {
  public:
    static uint8_t apply(uint8_t value) { return brightnessTable[value]; }

  private:
    static constexpr uint8_t brightnessTable[64] =
        {
            0, 0, 0, 1, 1, 1, 1, 1,
            2, 2, 3, 3, 4, 4, 5, 6,
            7, 8, 9, 10, 12, 14, 16, 18,
            20, 22, 25, 28, 31, 34, 37, 40,
            43, 46, 49, 52, 55, 57, 59, 60,
            61, 62, 63, 63, 63, 63, 63, 63,
            63, 63, 63, 63, 63, 63, 63, 63,
            63, 63, 63, 63, 63, 63, 63, 63};
  };
}
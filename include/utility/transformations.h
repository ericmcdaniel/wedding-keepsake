#pragma once

#include <stdint.h>

namespace Utility
{
  template <uint16_t Size>
  struct EaseCurve
  {
    uint16_t values[Size];

    constexpr EaseCurve() : values{}
    {
      uint16_t value = 1;

      for (uint16_t i = 0; i < Size; i++)
      {
        values[i] = value;
        value <<= 2;
        if (value > 255)
        {
          value = 255;
        }
      }
    }

    constexpr uint16_t operator[](uint16_t index) const
    {
      return values[index];
    }
  };
}
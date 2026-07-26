#pragma once

#include <stdint.h>

namespace Utilities
{
  template <uint32_t Size, uint32_t MaxValue = 255, uint32_t Shift = 2>
  struct EaseOutCurve
  {
    uint32_t values[Size];

    constexpr EaseOutCurve() : values{}
    {
      uint16_t value = 1;
      for (uint32_t i = 0; i < Size; i++)
      {
        values[i] = value;
        value <<= Shift;

        if (value > MaxValue)
        {
          value = MaxValue;
        }
      }
    }

    constexpr uint32_t operator[](uint32_t index) const
    {
      return values[index];
    }

    constexpr uint32_t map(uint32_t index, uint32_t min, uint32_t max) const
    {
      return min + ((max - min) * values[index]) / MaxValue;
    }
  };
}
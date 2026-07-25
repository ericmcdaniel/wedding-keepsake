#pragma once

#include <stdint.h>

namespace Utility
{
  template <int8_t Size>
  struct EaseCurve
  {
    int8_t values[Size];

    constexpr EaseCurve() : values{}
    {
      int16_t value = 255;

      for (int8_t i = 0; i < Size; i++)
      {
        values[i] = value;
        value >>= 1;
      }
    }

    constexpr int8_t operator[](int8_t index) const
    {
      return values[index];
    }
  };
}
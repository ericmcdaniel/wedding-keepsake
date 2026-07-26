#pragma once

#include <stdint.h>

namespace Utilities
{
  template <typename T, uint16_t N>
  constexpr uint16_t arraySize(const T (&)[N]) { return N; }

  template <typename T>
  constexpr T next(T value)
  {
    return static_cast<T>((static_cast<uint8_t>(value) + 1) % static_cast<uint8_t>(T::COUNT));
  }

  template <typename T>
  constexpr void advance(T &value)
  {
    value = next(value);
  }
}
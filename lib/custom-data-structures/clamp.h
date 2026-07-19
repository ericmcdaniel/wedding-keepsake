/*
  A simplified implementation of std::clamp<T>
*/
#pragma once

namespace CustomDataStructures
{
  template <typename T>
  constexpr T clamp(const T &value, const T &low, const T &high)
  {
    if (value < low)
      return low;

    if (high < value)
      return high;

    return value;
  }
}
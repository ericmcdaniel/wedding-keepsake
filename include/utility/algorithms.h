#pragma once

#include <stdint.h>

namespace Utility
{

  /*
    A simplified implementation of std::clamp<T>
  */
  template <typename T>
  constexpr T clamp(const T &value, const T &low, const T &high)
  {
    if (value < low)
      return low;

    if (high < value)
      return high;

    return value;
  }

  /*
    A simplified implementation of std::max<T>
  */
  template <typename T>
  T maxOf(T value)
  {
    return value;
  }

  /*
    A simplified implementation of std::max<T>
  */
  template <typename T, typename... Args>
  T maxOf(T first, Args... rest)
  {
    T max = maxOf(rest...); // recursive, yeah, but I mean how large does this ever scale?
    return first > max ? first : max;
  }
}
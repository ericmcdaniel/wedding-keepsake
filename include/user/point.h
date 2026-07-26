#pragma once

#include <stdint.h>

namespace User
{
  struct Point
  {
    int8_t x = 0;
    int8_t y = 0;

    constexpr Point(int8_t x = 0, int8_t y = 0) : x(x), y(y) {}

    void move(int8_t dx, int8_t dy)
    {
      x += dx;
      y += dy;
    }
  };
}
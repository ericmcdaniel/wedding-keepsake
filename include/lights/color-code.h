#pragma once

#include <stdint.h>

namespace Lights
{
  enum class ColorCode : uint32_t
  {
    Blue = 0x0000ff,
    Red = 0xff0000,
    Green = 0x009100,
    Yellow = 0xffff00,
    Gray = 0x476c6c,
  };
}
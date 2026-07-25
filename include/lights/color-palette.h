#pragma once

#include <stdint.h>

namespace Lights
{
  constexpr uint32_t pico8Palette[8] = {
      0xffe2ce,
      0xf56214,
      0xffc414,
      0x3bd827,
      0x147658,
      0x14c4ce,
      0x1d3162,
      0xa73176};

  constexpr uint8_t pico8PaletteSize = sizeof(pico8Palette) / sizeof(pico8Palette[0]);
}
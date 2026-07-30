#pragma once

#include "lights/color.h"
#include "stdint.h"

namespace User
{
  struct Texture
  {
    uint8_t width;
    uint8_t height;

    const uint32_t *pixels;
  };
}
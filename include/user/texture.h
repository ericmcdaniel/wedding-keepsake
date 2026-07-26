#pragma once

#include "lights/color.h"
#include "stdint.h"

namespace User
{
  struct Sprite
  {
    uint8_t width;
    uint8_t height;

    const Lights::Color *pixels;
  };
}
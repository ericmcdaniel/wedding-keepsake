#pragma once

#include <stdint.h>
#include "lights/color-code.h"
#include "clamp.h"

namespace Lights
{
  class Color
  {
  public:
    Color() : r{0}, g{0}, b{0} {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : r{red}, g{green}, b{blue} {}
    Color(uint32_t rgb);
    Color(ColorCode colorCode) : Color{static_cast<uint32_t>(colorCode)} {}

    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color operator*(double scale) const
    {
      Color result;
      result.r = static_cast<uint8_t>(CustomDataStructures::clamp(r * scale, 0.0, 255.0));
      result.g = static_cast<uint8_t>(CustomDataStructures::clamp(g * scale, 0.0, 255.0));
      result.b = static_cast<uint8_t>(CustomDataStructures::clamp(b * scale, 0.0, 255.0));
      return result;
    }

    Color operator*(uint8_t scale) const
    {
      Color result;
      result.r = (r * scale) / 255;
      result.g = (g * scale) / 255;
      result.b = (b * scale) / 255;
      return result;
    }

    Color operator/(double scale) const
    {
      Color result;
      result.r = static_cast<uint8_t>(CustomDataStructures::clamp(r / scale, 0.0, 255.0));
      result.g = static_cast<uint8_t>(CustomDataStructures::clamp(g / scale, 0.0, 255.0));
      result.b = static_cast<uint8_t>(CustomDataStructures::clamp(b / scale, 0.0, 255.0));
      return result;
    }

    Color operator/(uint8_t scale) const
    {
      Color result;
      result.r = (r / scale) / 255;
      result.g = (g / scale) / 255;
      result.b = (b / scale) / 255;
      return result;
    }

    Color &operator*=(double scale)
    {
      r = static_cast<uint8_t>(CustomDataStructures::clamp(r * scale, 0.0, 255.0));
      g = static_cast<uint8_t>(CustomDataStructures::clamp(g * scale, 0.0, 255.0));
      b = static_cast<uint8_t>(CustomDataStructures::clamp(b * scale, 0.0, 255.0));
      return *this;
    }
  };
}
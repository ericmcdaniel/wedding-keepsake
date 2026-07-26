#pragma once

#include "platform/configuration.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-brightness.h"

namespace Lights
{
  class LedMatrix
  {
  public:
    LedMatrix();

    Color &operator()(int8_t row, int8_t column) { return buffer(row, column); }
    const Color &operator()(int8_t row, int8_t column) const { return buffer(row, column); }

    Color &operator[](int8_t index) { return buffer[index]; }
    const Color &operator[](int8_t index) const { return buffer[index]; }

    Color *getRawColors();
    void reset();

  private:
    LedBuffer buffer;
    LedBrightness brightness;
  };
}
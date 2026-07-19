#pragma once

#include "platform/configuration.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"

namespace Lights
{
  class LedMatrix
  {
  public:
    LedMatrix();

    Color &operator()(uint8_t row, uint8_t column) { return buffer(row, column); }
    const Color &operator()(uint8_t row, uint8_t column) const { return buffer(row, column); }

    Color &operator[](uint16_t index) { return buffer[index]; }
    const Color &operator[](uint16_t index) const { return buffer[index]; }

    Color *getRawColors();
    void reset();
    void adjustLuminance();

  private:
    LedBuffer buffer;
    LedLuminance luminance;
  };
}
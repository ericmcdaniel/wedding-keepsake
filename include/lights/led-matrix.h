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

    Color &operator()(int8_t xIndex, int8_t yIndex) { return buffer(xIndex, yIndex); }
    const Color &operator()(int8_t xIndex, int8_t yIndex) const { return buffer(xIndex, yIndex); }

    Color &operator[](int8_t index) { return buffer[index]; }
    const Color &operator[](int8_t index) const { return buffer[index]; }

    Color *getRawColors();
    void reset();

  private:
    LedBuffer buffer;
    LedBrightness brightness;
  };
}
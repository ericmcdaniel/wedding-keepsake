#pragma once

#include <stdint.h>

#include "platform/configuration.h"
#include "lights/color.h"

namespace Lights
{
  class LedBuffer
  {
  public:
    LedBuffer() : leds{new Color[Platform::Configuration::numRows * Platform::Configuration::numColumns]} {}
    ~LedBuffer() { delete[] leds; }
    LedBuffer(LedBuffer &&other) = delete;
    LedBuffer &operator=(LedBuffer &&other) = delete;
    LedBuffer(const LedBuffer &other) = delete;
    LedBuffer &operator=(const LedBuffer &other) = delete;

    Color &operator()(int8_t xIndex, int8_t yIndex) { return leds[(yIndex * Platform::Configuration::numColumns) + xIndex]; }
    const Color &operator()(int8_t xIndex, int8_t yIndex) const { return leds[(yIndex * Platform::Configuration::numColumns) + xIndex]; }

    const int8_t size() const { return Platform::Configuration::numRows * Platform::Configuration::numColumns; }

    Color &operator[](int8_t index) { return leds[index]; }
    const Color &operator[](int8_t index) const { return leds[index]; }

    Color *data() { return leds; }
    const Color *data() const { return leds; }

  private:
    Color *leds;
  };
}
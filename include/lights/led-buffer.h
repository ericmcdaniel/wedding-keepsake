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

    Color &operator()(int8_t row, int8_t column) { return leds[(row * Platform::Configuration::numColumns) + column]; }
    const Color &operator()(int8_t row, int8_t column) const { return leds[(row * Platform::Configuration::numColumns) + column]; }

    int8_t size() const { return Platform::Configuration::numRows * Platform::Configuration::numColumns; }

    Color &operator[](int8_t index) { return leds[index]; }
    const Color &operator[](int8_t index) const { return leds[index]; }

    Color *data() { return leds; }
    const Color *data() const { return leds; }

  private:
    Color *leds;
  };
}
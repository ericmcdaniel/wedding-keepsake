#pragma once

#include "platform/configuration.h"
#include "lights/color.h"
#include "lights/led-buffer.h"
#include "lights/led-luminance.h"
// #include "engine/layer.h"

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
    static const uint16_t size() { return Platform::Configuration::numLeds; }
    void reset();
    void adjustLuminance();

    // Engine::Layer layer[Platform::Configuration::maxLeds];

  private:
    LedBuffer buffer;
    LedLuminance luminance;
  };
}
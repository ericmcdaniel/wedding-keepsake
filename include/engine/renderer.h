#pragma once

#include "lights/led-matrix.h"

namespace Engine
{
  class Renderer
  {
  public:
    void drawPixel(const Lights::Color &color, const uint16_t index);
    void drawPixel(const Lights::Color &color, const uint16_t row, const uint16_t col);

    void fillSolid(const Lights::Color &color);
    void fillLine(const Lights::Color &color, const uint16_t start, const uint16_t end); // inclusive

    void reset() { leds.reset(); }

    Lights::Color &getPixel(uint16_t row, uint16_t column)
    {
      return leds(row, column);
    }

    const Lights::Color &getPixel(uint16_t row, uint16_t column) const
    {
      return leds(row, column);
    }

  private:
    Lights::LedMatrix leds;
  };
}
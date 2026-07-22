#pragma once

#include "lights/led-matrix.h"

namespace Engine
{
  class Renderer
  {
  public:
    void drawPixel(const Lights::Color &color, const uint16_t row, const uint16_t col);
    void drawHorizontalLine(const Lights::Color &color, const uint16_t row, const uint16_t start, const uint16_t end);  // inclusive boundary
    void drawVerticalLine(const Lights::Color &color, const uint16_t column, const uint16_t start, const uint16_t end); // also inclusive
    void drawSolidRect(const Lights::Color &color, const uint16_t tlx, const uint16_t tly, const uint16_t brx, const uint16_t bry);
    void drawFullCanvas(const Lights::Color &color);
    void reset() { leds.reset(); }

    Lights::Color &getPixel(uint16_t row, uint16_t column) { return leds(row, column); }
    const Lights::Color &getPixel(uint16_t row, uint16_t column) const { return leds(row, column); }

  private:
    Lights::LedMatrix leds;
    inline bool checkVerticalBoundary(const uint16_t coordinate);
    inline bool checkHorizontalBoundary(const uint16_t coordinate);
    inline bool checkReverseOrder(const uint16_t start, const uint16_t end);
  };
}
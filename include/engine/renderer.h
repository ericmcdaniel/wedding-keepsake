#pragma once

#include "lights/led-matrix.h"

namespace Engine
{
  class Renderer
  {
  public:
    void drawPixel(const Lights::Color &color, const int8_t row, const int8_t col);
    void drawHorizontalLine(const Lights::Color &color, const int8_t row, const int8_t start, const int8_t end);  // inclusive boundary
    void drawVerticalLine(const Lights::Color &color, const int8_t column, const int8_t start, const int8_t end); // also inclusive
    void drawSolidRect(const Lights::Color &color, const int8_t tlx, const int8_t tly, const int8_t brx, const int8_t bry);
    void drawFullCanvas(const Lights::Color &color);
    void reset() { leds.reset(); }

    Lights::Color &getPixel(int8_t row, int8_t column) { return leds(row, column); }
    const Lights::Color &getPixel(int8_t row, int8_t column) const { return leds(row, column); }

  private:
    Lights::LedMatrix leds;
    inline bool checkVerticalBoundary(const int8_t coordinate);
    inline bool checkHorizontalBoundary(const int8_t coordinate);
    inline bool checkReverseOrder(const int8_t start, const int8_t end);
  };
}
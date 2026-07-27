#pragma once

#include "lights/led-matrix.h"

namespace Engine
{
  class Renderer
  {
  public:
    void renderPixel(const Lights::Color &color, const int8_t xPos, const int8_t yPos);
    void renderPixel(const Lights::Color &color, const int8_t index);
    void renderHorizontalLine(const Lights::Color &color, const int8_t yPos, const int8_t xStart, const int8_t xEnd); // inclusive boundary
    void renderVerticalLine(const Lights::Color &color, const int8_t xPos, const int8_t yStart, const int8_t yEnd);   // also inclusive
    void renderSolidRect(const Lights::Color &color, const int8_t tlx, const int8_t tly, const int8_t brx, const int8_t bry);
    void renderFullCanvas(const Lights::Color &color);
    void clearDisplay() { leds.reset(); }

    const Lights::Color &getPixel(int8_t xPos, int8_t yPos) const { return leds(xPos, yPos); }

  private:
    Lights::LedMatrix leds;
    inline bool checkValidYAxisBoundary(const int8_t coordinate);
    inline bool checkValidXAxisBoundary(const int8_t coordinate);
    inline bool checkReverseOrder(const int8_t start, const int8_t end);
  };
}
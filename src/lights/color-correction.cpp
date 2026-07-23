#include "lights/color-correction.h"
#include "utility/algorithms.h"

using namespace Lights;

Color ColorCorrection::apply(const Color &color)
{
  uint16_t r = color.r * redGain >> 8;
  uint16_t g = color.g * greenGain >> 8;
  uint16_t b = color.b * blueGain >> 8;

  uint16_t maxVal = Utility::maxOf(r, g, b);

  if (maxVal > 255)
  {
    r = r * 255 / maxVal;
    g = g * 255 / maxVal;
    b = b * 255 / maxVal;
  }

  return {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
}

uint8_t ColorCorrection::applyGain(uint8_t value, uint16_t gain)
{
  return static_cast<uint8_t>((static_cast<uint16_t>(value) * gain) >> 8);
}

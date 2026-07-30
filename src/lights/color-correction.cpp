#include "lights/color-correction.h"
#include "utilities/algorithms.h"

using namespace Lights;

Color ColorCorrection::apply(const Color &color)
{
  uint16_t r = applyGain(color.r, redGain);
  uint16_t g = applyGain(color.g, greenGain);
  uint16_t b = applyGain(color.b, blueGain);

  uint16_t maxVal = Utilities::maxOf(r, g, b);

  if (maxVal > 255)
  {
    r = static_cast<uint16_t>((static_cast<uint32_t>(r) * 255) / maxVal);
    g = static_cast<uint16_t>((static_cast<uint32_t>(g) * 255) / maxVal);
    b = static_cast<uint16_t>((static_cast<uint32_t>(b) * 255) / maxVal);
  }

  return {
      static_cast<uint8_t>(r),
      static_cast<uint8_t>(g),
      static_cast<uint8_t>(b)};
}

uint16_t ColorCorrection::applyGain(uint8_t value, uint16_t gain)
{
  return static_cast<uint16_t>((static_cast<uint32_t>(value) * gain) >> 8);
}

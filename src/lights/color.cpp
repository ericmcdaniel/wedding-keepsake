#include "lights/color.h"

using namespace Lights;

Color::Color(uint32_t rawRgb)
{
  r = static_cast<uint8_t>((rawRgb >> 16) & 0xFF);
  g = static_cast<uint8_t>((rawRgb >> 8) & 0xFF);
  b = static_cast<uint8_t>(rawRgb & 0xFF);
}
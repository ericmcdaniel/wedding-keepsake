#include "lights/led-matrix.h"

using namespace Lights;

LedMatrix::LedMatrix()
{
  reset();
}

Color *LedMatrix::getRawColors()
{
  return static_cast<Color *>(buffer.data());
}

void LedMatrix::reset()
{
  for (uint16_t i = 0; i < Platform::Configuration::numLeds; i++)
  {
    buffer[i] = Color{};
  }
}

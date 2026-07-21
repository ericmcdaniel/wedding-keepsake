#include "engine/renderer.h"

using namespace Engine;

void Renderer::drawPixel(const Lights::Color &color, const uint16_t index)
{
  if (index < 0 || index >= Platform::Configuration::numLeds)
    return;

  leds[index] = color;
}

void Renderer::drawPixel(const Lights::Color &color, const uint16_t row, const uint16_t col)
{
  if (row < 0 || col < 0)
    return;

  if (row >= Platform::Configuration::numRows || col >= Platform::Configuration::numColumns)
    return;

  leds(row, col) = color;
}

void Renderer::fillSolid(const Lights::Color &color)
{
  for (uint16_t i = 0; i < Platform::Configuration::numLeds; i++)
  {
    leds[i] = color;
  }
}

void Renderer::fillLine(const Lights::Color &color, const uint16_t start, const uint16_t end)
{
  // End is inclusive. The boundary will however be checked.

  if (start < 0 || end >= Platform::Configuration::numLeds)
    return;

  if (end < start)
    return;

  for (uint16_t i = start; i <= end; i++)
  {
    leds[i] = color;
  }
}

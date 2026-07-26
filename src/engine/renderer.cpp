#include "engine/renderer.h"
#include "utilities/logger.h"

using namespace Engine;

void Renderer::drawPixel(const Lights::Color &color, const int8_t row, const int8_t col)
{
  if (checkHorizontalBoundary(col) || checkVerticalBoundary(row))
  {
    logf("Received value out of boundary: row=%u col=%u", row, col);
    return;
  }

  leds[row * Platform::Configuration::numColumns + col] = color;
}

void Renderer::drawPixel(const Lights::Color &color, const int8_t index)
{
  if (index < 0 || index >= Platform::Configuration::numLeds)
  {
    logf("Received value out of boundary: index=%u", index);
    return;
  }

  leds[index] = color;
}

void Renderer::drawFullCanvas(const Lights::Color &color)
{
  for (int8_t i = 0; i < Platform::Configuration::numLeds; i++)
  {
    leds[i] = color;
  }
}

void Renderer::drawHorizontalLine(const Lights::Color &color, const int8_t row, const int8_t start, const int8_t end)
{
  // End is inclusive. The boundary will however be checked.
  if (checkHorizontalBoundary(start))
  {
    logf("Received value out of boundary: start=%u end=%u", start, end);
    return;
  }

  if (checkReverseOrder(start, end))
  {
    logf("Received invalid horizontal boundary, end cannot be before start: start=%u end=%u", start, end);
    return;
  }

  if (checkVerticalBoundary(row))
  {
    logf("Received invalid vertical boundary: row=%u", row);
  }

  for (int8_t i = start; i <= end; i++)
  {
    leds[row * Platform::Configuration::numColumns + i] = color;
  }
}

void Renderer::drawVerticalLine(const Lights::Color &color, const int8_t column, const int8_t start, const int8_t end)
{
  // End is inclusive. The boundary will however be checked.
  if (checkVerticalBoundary(start) || checkVerticalBoundary(end))
  {
    logf("Received value out of boundary: start=%u end=%u", start, end);
    return;
  }

  if (checkReverseOrder(start, end))
  {
    logf("Received invalid vertical boundary, end cannot be before start: start=%u end=%u", start, end);
    return;
  }

  if (checkHorizontalBoundary(column))
  {
    logf("Received invalid horizontal boundary: column=%u", column);
    return;
  }

  for (int8_t i = start; i <= end; i++)
  {
    leds[i * Platform::Configuration::numColumns + column] = color;
  }
}

void Renderer::drawSolidRect(const Lights::Color &color, const int8_t tlx, const int8_t tly, const int8_t brx, const int8_t bry)
{
  // draws a rectangle:
  //  *  tlx = top-left x-axis
  //  *  bry = bottom-right y-axis

  if (checkHorizontalBoundary(tlx))
  {
    logf("Received invalid top-left x-axis boundary. Expected tlx=0-7, Received tlx=%u", tlx);
    return;
  }
  if (checkHorizontalBoundary(brx))
  {
    logf("Received invalid bottom-right x-axis boundary. Expected brx=0-7, Received brx=%u", brx);
    return;
  }
  if (checkVerticalBoundary(tly))
  {
    logf("Received invalid top-left y-axis boundary. Expected tly=0-3, Received tly=%u", tly);
    return;
  }
  if (checkVerticalBoundary(bry))
  {
    logf("Received invalid bottom-right y-axis boundary. Expected bry=0-3, Received bry=%u", bry);
    return;
  }
  if (checkReverseOrder(tlx, brx) || checkReverseOrder(tly, bry))
  {
    logf("Received invalid boundaries. Reversed. Expected tlx <= brx and tyl <= bry, Received tlx=%u brx=%u tyl=%u bry=%u", tlx, brx, tly, bry);
    return;
  }

  for (int8_t row = tly; row <= bry; row++)
  {
    for (int8_t col = tlx; col <= brx; col++)
    {
      leds(row, col) = color;
    }
  }
}

inline bool Renderer::checkVerticalBoundary(const int8_t coordinate)
{
  return coordinate < 0 || coordinate >= Platform::Configuration::numRows;
}

inline bool Renderer::checkHorizontalBoundary(const int8_t coordinate)
{
  return coordinate < 0 || coordinate >= Platform::Configuration::numColumns;
}

inline bool Renderer::checkReverseOrder(const int8_t start, const int8_t end)
{
  return end < start;
}
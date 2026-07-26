#include "engine/renderer.h"
#include "utilities/logger.h"

using namespace Engine;

void Renderer::drawPixel(const Lights::Color &color, const int8_t xPos, const int8_t yPos)
{
  if (checkValidXAxisBoundary(xPos) || checkValidYAxisBoundary(yPos))
  {
    logf("Received value out of boundary. Coordinates: (%u, %u)", xPos, yPos);
    return;
  }

  leds[yPos * Platform::Configuration::numColumns + xPos] = color;
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

void Renderer::drawHorizontalLine(const Lights::Color &color, const int8_t yPos, const int8_t xStart, const int8_t xEnd)
{
  // End is inclusive. The boundary will however be checked.
  if (checkValidXAxisBoundary(xStart) || checkValidXAxisBoundary(xEnd))
  {
    logf("Received value out of boundary: xStart=%u xEnd=%u", xStart, xEnd);
    return;
  }

  if (checkReverseOrder(xStart, xEnd))
  {
    logf("Received invalid horizontal boundary, end cannot be before start: xStart=%u xEnd=%u", xStart, xEnd);
    return;
  }

  if (checkValidYAxisBoundary(yPos))
  {
    logf("Received invalid vertical boundary: yPos=%u", yPos);
  }

  for (int8_t i = xStart; i <= xEnd; i++)
  {
    leds[yPos * Platform::Configuration::numColumns + i] = color;
  }
}

void Renderer::drawVerticalLine(const Lights::Color &color, const int8_t xPos, const int8_t yStart, const int8_t yEnd)
{
  // End is inclusive. The boundary will however be checked.
  if (checkValidYAxisBoundary(yStart) || checkValidYAxisBoundary(yEnd))
  {
    logf("Received value out of boundary: yStart=%u yEnd=%u", yStart, yEnd);
    return;
  }

  if (checkValidXAxisBoundary(xPos))
  {
    logf("Received invalid horizontal boundary: xPos=%u", xPos);
    return;
  }

  if (checkReverseOrder(yStart, yEnd))
  {
    logf("Received invalid vertical boundary, end cannot be before start: yStart=%u yEnd=%u", yStart, yEnd);
    return;
  }

  for (int8_t i = yStart; i <= yEnd; i++)
  {
    leds[i * Platform::Configuration::numColumns + xPos] = color;
  }
}

void Renderer::drawSolidRect(const Lights::Color &color, const int8_t tlx, const int8_t tly, const int8_t brx, const int8_t bry)
{
  // draws a rectangle:
  //  *  tlx = top-left x-axis
  //  *  bry = bottom-right y-axis

  if (checkValidXAxisBoundary(tlx))
  {
    logf("Received invalid top-left x-axis boundary. Expected tlx=0-7, Received tlx=%u", tlx);
    return;
  }
  if (checkValidXAxisBoundary(brx))
  {
    logf("Received invalid bottom-right x-axis boundary. Expected brx=0-7, Received brx=%u", brx);
    return;
  }
  if (checkValidYAxisBoundary(tly))
  {
    logf("Received invalid top-left y-axis boundary. Expected tly=0-3, Received tly=%u", tly);
    return;
  }
  if (checkValidYAxisBoundary(bry))
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
      leds(col, row) = color;
    }
  }
}

inline bool Renderer::checkValidYAxisBoundary(const int8_t coordinate)
{
  return coordinate < 0 || coordinate >= Platform::Configuration::numRows;
}

inline bool Renderer::checkValidXAxisBoundary(const int8_t coordinate)
{
  return coordinate < 0 || coordinate >= Platform::Configuration::numColumns;
}

inline bool Renderer::checkReverseOrder(const int8_t start, const int8_t end)
{
  return end < start;
}
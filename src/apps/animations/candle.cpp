#include "apps/animations/candle.h"

using namespace Apps::Animations;

void Candle::nextEvent()
{
  if (isReady())
  {
    wait(idleTime + contextManager.entropy.random(150));
    animationState++;
  }

  for (int8_t i = 0; i < Platform::Configuration::numLeds; i++)
  {
    uint32_t patternIndex = 0;

    // alternates by inverting across the x-axis
    if (animationState % 2 == 0)
    {
      uint8_t row = i / Platform::Configuration::numColumns;
      uint8_t column = i % Platform::Configuration::numColumns;
      uint8_t invertedRow = Platform::Configuration::numRows - 1 - row;
      patternIndex = candlePattern[invertedRow * 8 + column];
    }
    else
    {
      patternIndex = candlePattern[i];
    }

    contextManager.renderer.drawPixel(Lights::Color{patternIndex}, i);
  }
}
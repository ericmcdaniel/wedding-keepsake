#include "apps/animations/american-flag.h"

using namespace Apps::Animations;

void AmericanFlag::nextEvent()
{
  if (isReady())
  {
    wait(75);
    wavePhase = (wavePhase + 1) & 0x0f;
  }

  for (uint8_t row = 0; row < 4; row++)
  {
    for (uint8_t column = 0; column < 8; column++)
    {
      uint8_t index = (row * 8) + column;

      uint8_t phase = (wavePhase - column) & 0x0f;
      uint8_t dim = waveTable[phase];

      uint8_t brightness = 255 - ((dim * waveAmplitude) >> 6);

      Lights::Color original{flagPattern[index]};
      Lights::Color color{
          uint8_t((uint16_t(original.r) * brightness) >> 8),
          uint8_t((uint16_t(original.g) * brightness) >> 8),
          uint8_t((uint16_t(original.b) * brightness) >> 8)};

      contextManager.renderer.drawPixel(color, index);
    }
  }
}
#include "apps/animations/rainbow.h"

using namespace Apps::Animations;

void Rainbow::nextEvent()
{
  colorPhase++;
  Lights::Color color = getRainbowColor(colorPhase);
  contextManager->renderer.fillSolid(color);
}

Lights::Color Rainbow::getRainbowColor(uint8_t phase)
{
  Lights::Color c;

  uint8_t section = phase / 43;
  uint8_t offset = (phase % 43) * 6;

  switch (section)
  {
  case 0:
    c = {255, offset, 0};
    break;
  case 1:
    c = {255 - offset, 255, 0};
    break;
  case 2:
    c = {0, 255, offset};
    break;
  case 3:
    c = {0, 255 - offset, 255};
    break;
  case 4:
    c = {offset, 0, 255};
    break;
  default:
    c = {255, 0, 255 - offset};
    break;
  }
  return c;
}

#include "apps/animations/rainbow.h"

using namespace Apps::Animations;

void Rainbow::nextEvent()
{
  if (isReady())
  {
    wait(115);
    contextManager->renderer.reset();

    colorPhaseShift++;
    Lights::Color color = getRainbowColor(colorPhaseShift);
    contextManager->renderer.drawFullCanvas(color);
  }
}

Lights::Color Rainbow::getRainbowColor(uint8_t phase)
{
  Lights::Color c;

  uint8_t section = phase / 43;
  uint8_t offset = (phase % 43) * 6;
  uint8_t max = 255;

  switch (section)
  {
  case 0:
    c = {max, offset, 0};
    break;
  case 1:
    c = {max - offset, max, 0};
    break;
  case 2:
    c = {0, max, offset};
    break;
  case 3:
    c = {0, max - offset, max};
    break;
  case 4:
    c = {offset, 0, max};
    break;
  default:
    c = {max, 0, max - offset};
    break;
  }
  return c;
}

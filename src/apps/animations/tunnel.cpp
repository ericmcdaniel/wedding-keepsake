#include "apps/animations/tunnel.h"

using namespace Apps::Animations;

void Tunnel::nextEvent()
{
  if (isReady())
  {
    wait(10);
    contextManager.renderer.clear();
    colorPhaseShift += 2;

    Lights::Color backgroundColor = getTunnelColor(colorPhaseShift);
    contextManager.renderer.drawFullCanvas(backgroundColor);

    Lights::Color outerColor = getTunnelColor(colorPhaseShift + 6);
    contextManager.renderer.drawSolidRect(outerColor, 1, 1, 6, 2);
    contextManager.renderer.drawSolidRect(outerColor, 3, 0, 4, 3);

    Lights::Color innerColor = getTunnelColor(colorPhaseShift + 14);
    contextManager.renderer.drawSolidRect(innerColor, 2, 1, 5, 2);

    Lights::Color core = getTunnelColor(colorPhaseShift + 30);
    contextManager.renderer.drawSolidRect(core, 3, 1, 4, 2);
  }
}

Lights::Color Tunnel::getTunnelColor(uint8_t phase)
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

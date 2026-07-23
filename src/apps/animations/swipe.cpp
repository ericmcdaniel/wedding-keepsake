#include "apps/animations/swipe.h"

using namespace Apps::Animations;

void Swipe::nextEvent()
{
  if (isReady())
  {
    wait(115);
    contextManager->renderer.reset();

    Lights::Color color = getSwipeColor();
    contextManager->renderer.drawFullCanvas(color);
  }
}

Lights::Color Swipe::getSwipeColor()
{
  // random color
}

#include "apps/animations/swipe.h"

using namespace Apps::Animations;

void Swipe::nextEvent()
{
  switch (state)
  {
  case SwipeState::Idle:
    handleIdleState();
    break;
  case SwipeState::Swiping:
    handleSwipeAnimation();
    break;
  }
  // if (isReady())
  // {
  //   wait(115);
  //   contextManager.renderer.reset();

  //   Lights::Color color = getSwipeColor();
  //   contextManager.renderer.drawFullCanvas(color);
  // }
}

void Swipe::handleIdleState()
{
  if (isReady())
  {
    state = SwipeState::Swiping;
    active = (active + 1) % 2;
    slot[active] = {contextManager.entropy.get() % 128, contextManager.entropy.get() % 128, contextManager.entropy.get() % 128};
    wait(900);
    return;
  }
  contextManager.renderer.reset();
  contextManager.renderer.drawFullCanvas(slot[active]);
}

void Swipe::handleSwipeAnimation()
{
}

Lights::Color Swipe::getSwipeColor()
{
  // random color
}

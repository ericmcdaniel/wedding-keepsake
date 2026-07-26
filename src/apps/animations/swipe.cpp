#include "apps/animations/swipe.h"
#include "utility/entropy.h"
#include "utility/common.h"

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
}

void Swipe::handleIdleState()
{
  if (isReady())
  {
    state = SwipeState::Swiping;
    activeColor = nextIndex();
    slot[activeColor] = getSwipeColor();
    return;
  }
  contextManager.renderer.clear();
  contextManager.renderer.drawFullCanvas(slot[activeColor]);
}

void Swipe::handleSwipeAnimation()
{
  drawSwipe();

  if (!isReady())
  {
    return;
  }

  if (swipeProgress >= Platform::Configuration::numColumns - 1)
  {
    swipeProgress = 0;
    state = SwipeState::Idle;
    direction = static_cast<Direction>((static_cast<uint8_t>(direction) + 1u) % 2);
    wait(idleWaitTime);
    return;
  }

  wait(swipeTiming.map(swipeProgress, minDelay, maxDelay));
  swipeProgress++;
}

Lights::Color Swipe::getSwipeColor()
{
  return Lights::Color{Lights::vividPalette[contextManager.entropy.random(8) % arraySize(Lights::vividPalette)]};
}

void Swipe::drawSwipe()
{
  switch (direction)
  {
  case Direction::Left:
    drawSwipeLeft();
    break;
  case Direction::Right:
    drawSwipeRight();
    break;
  }
}

void Swipe::drawSwipeRight()
{
  for (int8_t row = 0; row < Platform::Configuration::numRows; row++)
  {
    for (int8_t col = 0; col < Platform::Configuration::numColumns; col++)
    {
      if (col <= swipeProgress)
      {
        contextManager.renderer.drawPixel(slot[activeColor], row, col);
      }
      else
      {
        contextManager.renderer.drawPixel(slot[nextIndex()], row, col);
      }
    }
  }
}

void Swipe::drawSwipeLeft()
{
  for (int8_t row = 0; row < Platform::Configuration::numRows; row++)
  {
    for (int8_t col = Platform::Configuration::numColumns - 1; col >= 0; col--)
    {
      if (col >= Platform::Configuration::numColumns - 1 - swipeProgress)
      {
        contextManager.renderer.drawPixel(slot[activeColor], row, col);
      }
      else
      {
        contextManager.renderer.drawPixel(slot[nextIndex()], row, col);
      }
    }
  }
}
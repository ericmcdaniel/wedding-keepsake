#include "apps/animations/swipe.h"
#include "utilities/entropy.h"
#include "utilities/common.h"

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
  contextManager.renderer.clearDisplay();
  contextManager.renderer.renderFullCanvas(slot[activeColor]);
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
  return Lights::Color{Lights::vividPalette[contextManager.entropy.random(8) % Utilities::arraySize(Lights::vividPalette)]};
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
        contextManager.renderer.renderPixel(slot[activeColor], col, row);
      }
      else
      {
        contextManager.renderer.renderPixel(slot[nextIndex()], col, row);
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
        contextManager.renderer.renderPixel(slot[activeColor], col, row);
      }
      else
      {
        contextManager.renderer.renderPixel(slot[nextIndex()], col, row);
      }
    }
  }
}
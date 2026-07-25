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
    contextManager.renderer.clear();
    slot[activeColor] = getSwipeColor();
    wait(100);
    return;
  }
  contextManager.renderer.clear();
  contextManager.renderer.drawFullCanvas(slot[activeColor]);
}

void Swipe::handleSwipeAnimation()
{

  if (isReady())
  {
    swipeProgress++;

    if (swipeProgress >= Platform::Configuration::numColumns)
    {
      swipeProgress = 0;
      state = SwipeState::Idle;
      wait(900);
      return;
    }
  }
  drawSwipe();
}

Lights::Color Swipe::getSwipeColor()
{
  return Lights::Color{Lights::pico8Palette[contextManager.entropy.random() % arraySize(Lights::pico8Palette)]};
}

void Swipe::drawSwipe()
{
  switch (direction)
  {
  case Direction::Up:
  case Direction::Down:
  case Direction::Left:
  case Direction::Right:
    drawSwipeRight();
    break;
  }
}

void Swipe::drawSwipeRight()
{
  for (uint8_t row = 0; row < Platform::Configuration::numRows; row++)
  {
    for (uint8_t col = 0; col < Platform::Configuration::numColumns; col++)
    {
      int8_t distance = col - swipeProgress;

      if (distance <= 0)
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
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

  if (isReady())
  {
    swipeProgress++;

    wait(25);

    if (swipeProgress >= Platform::Configuration::numColumns)
    {
      swipeProgress = 0;
      state = SwipeState::Idle;
      wait(900);
    }
  }
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
  uint8_t revealColumn = swipeEase[swipeProgress];

  if (revealColumn >= Platform::Configuration::numColumns)
  {
    revealColumn = Platform::Configuration::numColumns - 1;
  }

  for (uint8_t row = 0; row < Platform::Configuration::numRows; row++)
  {
    for (uint8_t col = 0; col < Platform::Configuration::numColumns; col++)
    {
      if (col <= revealColumn)
      {
        contextManager.renderer.drawPixel(slot[nextIndex()], row, col);
      }
      else
      {
        contextManager.renderer.drawPixel(slot[activeColor], row, col);
      }
    }
  }
}
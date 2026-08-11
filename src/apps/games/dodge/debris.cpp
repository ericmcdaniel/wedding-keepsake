#include "apps/games/dodge/debris.h"
#include "platform/configuration.h"

using namespace Apps::Game::Dodge;

void Debris::updatePosition()
{
  if (isReady())
  {
    position.x -= 1;
    if (position.x <= -width)
    {
      deactivate();
    }
    wait(speed);
  }
}

void Debris::activate(uint32_t s)
{
  active = true;
  speed = s;
}

void Debris::deactivate()
{
  completedCycle = true;
  reset();
};

void Debris::reset()
{
  active = false;

  uint32_t randInt = contextManager.entropy.random();
  switch (randInt % 3)
  {
  case 0:
    texture = {width, height, orangePalette};
    break;
  case 1:
    texture = {width, height, redPalette};
    break;
  case 2:
    texture = {width, height, greenPalette};
    break;
  }

  if (randInt % 2 == 0)
  {
    position = topPosition;
  }
  else
  {
    position = bottomPosition;
  }
}

void Debris::render()
{
  for (int8_t row = 0; row < height; row++)
  {
    for (int8_t col = 0; col < width; col++)
    {
      contextManager.renderer.renderPixel(texture.pixels[row * width + col], position.x + col, position.y + row);
    }
  }
}
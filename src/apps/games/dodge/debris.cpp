#include "apps/games/dodge/debris.h"
#include "platform/configuration.h"

using namespace Apps::Game::Dodge;

void Debris::updatePosition()
{
  position.x -= 1;
  if (position.x <= -2)
  {
    active = false;
    completedCycle = true;
    speed = 0;
  }
}

void Debris::activate(int8_t s)
{
  active = true;
  completedCycle = false;
  speed = s;
  position = Platform::Configuration::numLeds;
}

void Debris::reset()
{
  active = false;
  speed = 0;
  // impacted = false;
  position = Platform::Configuration::numColumns;
}

void Debris::render()
{
  for (int8_t row = 0; row < height; row++)
  {
    for (int8_t col = 0; col < width; col++)
    {
      contextManager.renderer.renderPixel(texture[row * width + col], position.x + col, position.y + row);
    }
  }
}
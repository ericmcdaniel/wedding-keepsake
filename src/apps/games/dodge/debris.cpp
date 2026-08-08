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
    wait(250);
  }
}

void Debris::activate()
{
  active = true;
  position = Platform::Configuration::numColumns;
}

void Debris::deactivate()
{
  if (contextManager.time.getMillisecond() - lastRespawnTime >= respawnTime)
  {
    lastRespawnTime = contextManager.time.getMillisecond();
    active = false;
    position = Platform::Configuration::numColumns;
  }
};

void Debris::reset()
{
  active = false;
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
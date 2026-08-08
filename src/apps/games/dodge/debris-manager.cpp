#include "apps/games/dodge/debris-manager.h"
#include "utilities/common.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void DebrisManager::dispatch(uint32_t speed)
{
  for (auto &debris : debrisPool)
  {
    if (!debris.isActive())
    {
      debris.activate(speed);
      log("debris dispatched");
      return;
    }
  }
  logf("debris dispatch: no free slots remaining");
}

void DebrisManager::render()
{
  for (const auto &debris : debrisPool)
  {
    if (!debris.isActive())
      continue;

    for (int8_t row = 0; row < debris.height; row++)
    {
      for (int8_t col = 0; col < debris.width; col++)
      {
        contextManager.renderer.renderPixel(debris.texture[row * debris.width + col], debris.position.x + col, debris.position.y + row);
      }
    }
  }
  logf("Debris[0]=%d, Debris[1]=%d, Debris[2]=%d, Debris[3]=%d", debrisPool[0].position.x, debrisPool[1].position.x, debrisPool[2].position.x, debrisPool[3].position.x);
}

void DebrisManager::updatePositions()
{
  for (auto &debris : debrisPool)
  {
    if (!debris.isActive())
      continue;

    debris.updatePosition();

    if (debris.completedCycle)
    {
      // TODO: update game score here
      debris.completedCycle = false;
    }
  }
}

const uint8_t DebrisManager::size() const
{
  uint8_t count = 0;
  for (const auto &debris : debrisPool)
  {
    if (debris.isActive())
    {
      count++;
    }
  }
  return count;
}

void DebrisManager::reset()
{
  for (Debris &debris : debrisPool)
  {
    debris.reset();
  }
}

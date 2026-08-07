#include "apps/games/dodge/debris-manager.h"
#include "utilities/common.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void DebrisManager::dispatch(uint8_t speed)
{
  for (auto &debris : debrisPool)
  {
    if (!debris.isActive())
    {
      debris.activate(speed);
      logf("debris dispatched with speed %u", speed);
      return;
    }
  }
  logf("debris dispatch: no free slots remaining");
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

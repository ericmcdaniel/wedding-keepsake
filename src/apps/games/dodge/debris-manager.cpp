#include "apps/games/dodge/debris-manager.h"
#include "apps/games/dodge/player.h"
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

bool DebrisManager::checkCollision(const Player &player)
{
  for (const auto &debris : debrisPool)
  {
    if (player.intersects(debris))
    {
      return true;
    }
  }
  return false;
}

void DebrisManager::render()
{
  for (auto &debris : debrisPool)
  {
    if (!debris.isActive())
      continue;

    debris.render();
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

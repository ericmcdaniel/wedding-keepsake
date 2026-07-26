#include "apps/games/dodge/dodge-main.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void DodgeMain::nextEvent()
{
  if (isReady())
  {
    wait(20);

    contextManager.renderer.clear();
    player.render();

    if (contextManager.button.wasDoublePress())
    {
      log("Double press fired.");
    }
    else if (contextManager.button.wasSinglePress())
    {
      log("Single press fired.");
    }
  }
}
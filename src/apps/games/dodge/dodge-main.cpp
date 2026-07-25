#include "apps/games/dodge/dodge-main.h"
#include "utility/logger.h"

using namespace Apps::Game;

void Apps::Game::DodgeMain::nextEvent()
{
  if (isReady())
  {
    wait(20);

    contextManager.renderer.clear();
    contextManager.renderer.drawSolidRect({255, 255, 255}, 3, 1, 4, 2);

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
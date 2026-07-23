#include "apps/game/temporary-placeholder.h"
#include "logger.h"

using namespace Apps::Game;

void Apps::Game::TemporaryPlaceholder::nextEvent()
{
  contextManager->renderer.reset();
  if (contextManager->button.wasDoublePress())
  {
    log("Double press fired.");
  }
  else if (contextManager->button.wasSinglePress())
  {
    log("Single press fired.");
  }
}
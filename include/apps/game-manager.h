#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "apps/game/temporary-placeholder.h"
#include "logger.h"

namespace Apps
{
  class GameManager : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    GameManager(Platform::ContextManager *ctx) : contextManager{ctx}
    {
      currentGame = new Apps::Game::TemporaryPlaceholder{contextManager};
      log("Initializing GameManager with TemporaryPlaceholder (TBD).");
    }

    ~GameManager()
    {
      delete currentGame;
      currentGame = nullptr;
    }

    void nextEvent() override;

  private:
    Platform::ContextManager *contextManager;
    Engine::ApplicationRuntime *currentGame = nullptr;
  };
}
#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "apps/games/dodge/dodge-main.h"
#include "utilities/logger.h"

namespace Apps
{
  class GameManager : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    GameManager(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      currentGame = new Apps::Game::Dodge::DodgeMain{contextManager};
      log("Initializing GameManager with DodgeMain.");
    }

    ~GameManager()
    {
      delete currentGame;
      currentGame = nullptr;
    }

    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;
    Engine::ApplicationRuntime *currentGame = nullptr;
  };
}
#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "apps/games/dodge/player.h"

namespace Apps::Game::Dodge
{
  class DodgeMain : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    DodgeMain(Platform::ContextManager &ctx) : Engine::Timer{ctx.time},
                                               contextManager{ctx},
                                               player{ctx}
    {
      wait(20);
    }
    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;
    Player player;
  };
}
#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "apps/games/dodge/player.h"
#include "apps/games/dodge/debris.h"

namespace Apps::Game::Dodge
{
  enum class State
  {
    BeginGame,
    Playing
  };

  class Main : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Main(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}, player{ctx}, backgroundTimer{ctx.time}, debisPool{ctx, ctx, ctx, ctx}
    {
      wait(750);
      backgroundTimer.wait(backgroundRenderRate);
    }
    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;
    State state = State::BeginGame;
    Player player;
    Debris debisPool[4];

    void updateDebrisPositions();
    void handleStartup();
    void handleBackground();
    void handleGamePlay();
    void render();

    static constexpr uint32_t startDeplayTime = 110;
    Engine::Timer backgroundTimer;
    uint32_t backgroundRenderRate = 200; // 80;
    uint8_t backgroundRepeatLength = 8;
  };
}
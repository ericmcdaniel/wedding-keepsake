#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "apps/games/dodge/player.h"
#include "apps/games/dodge/debris.h"
#include "apps/games/dodge/debris-manager.h"
#include "apps/games/dodge/level-manager.h"

namespace Apps::Game::Dodge
{
  enum class State
  {
    BeginGame,
    Playing,
    Winddown,
    CollisionMuzzleFlash,
    GameOver,
    DisplayScore
  };

  class Main : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Main(Platform::ContextManager &ctx) : Engine::Timer{ctx.time},
                                          contextManager{ctx},
                                          player{ctx},
                                          debrisManager{ctx},
                                          backgroundTimer{ctx.time},
                                          winddownTimer{ctx.time}
    {
      wait(750);
      backgroundTimer.wait(levelManager[level].backgroundSpeed);
      winddownTimer.wait(10000);
    }
    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;
    State state = State::BeginGame;
    Player player;
    DebrisManager debrisManager;
    LevelManager levelManager;

    void prepareUser();
    void handleBackground();
    void nextUpdate();
    void assessDifficulty();
    void checkCollisions();
    void checkContinue(State state);
    void playAnimationSequence();
    void render();
    void renderMuzzleFlash();
    void renderGameOver();
    void renderScore();
    void reset();

    uint8_t level = 0;
    uint16_t debrisDodged = 0;

    Engine::Timer backgroundTimer;
    Engine::Timer winddownTimer;
    static constexpr uint32_t gameStartAnimationSpeed = 100;
  };
}
#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "utility/entropy.h"

namespace Apps::Animations
{
  enum class Direction
  {
    Up,
    Right,
    Down,
    Left
  };

  enum class SwipeState
  {
    Idle,
    Swiping
  };

  class Swipe : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Swipe(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      wait(25);
      slot[0] = {contextManager.entropy.get() % 256u, contextManager.entropy.get() % 256u, contextManager.entropy.get() % 256u};
      slot[1] = {contextManager.entropy.get() % 256u, contextManager.entropy.get() % 256u, contextManager.entropy.get() % 256u};
    }
    void nextEvent() override;

    Lights::Color getSwipeColor();

  private:
    Platform::ContextManager &contextManager;
    Direction direction = Direction::Up;
    SwipeState state = SwipeState::Idle;

    Lights::Color slot[2];
    uint8_t active = 0;

    void handleIdleState();
    void handleSwipeAnimation();
  };
}
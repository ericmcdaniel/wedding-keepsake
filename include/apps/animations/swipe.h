#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "lights/color-palette.h"

namespace Apps::Animations
{
  enum class Direction
  {
    Up,
    Right,
    Down,
    Left,
    COUNT
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
      ctx.renderer.clear();
      slot[0] = getSwipeColor();
      slot[1] = getSwipeColor();
    }
    void nextEvent() override;

    Lights::Color getSwipeColor();

  private:
    Platform::ContextManager &contextManager;
    Direction direction = contextManager.entropy.randomEnum(Direction::COUNT);
    SwipeState state = SwipeState::Swiping;

    Lights::Color slot[2];
    uint8_t activeColor = 0;
    int8_t swipeProgress = 0;

    void handleIdleState();
    void handleSwipeAnimation();
    void drawSwipe();
    void drawSwipeRight();
    inline const uint8_t nextIndex() const { return (activeColor + 1) % 2; }
  };
}
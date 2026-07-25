#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "lights/color-palette.h"
#include "utility/transformations.h"

namespace Apps::Animations
{
  enum class Direction
  {
    Left,
    Right
  };

  enum class SwipeState
  {
    Idle,
    Swiping
  };

  constexpr Utility::EaseCurve<Platform::Configuration::numColumns> swipeTiming;

  class Swipe : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Swipe(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      ctx.renderer.clear();
      wait(idleWaitTime);
      slot[0] = getSwipeColor();
      slot[1] = getSwipeColor();
    }
    void nextEvent() override;

    Lights::Color getSwipeColor();

  private:
    Platform::ContextManager &contextManager;
    Direction direction = Direction::Right;
    SwipeState state = SwipeState::Idle;
    static constexpr uint32_t idleWaitTime = 900;

    Lights::Color slot[2];
    uint8_t activeColor = 0;
    int8_t swipeProgress = 0;

    void handleIdleState();
    void handleSwipeAnimation();
    void drawSwipe();
    void drawSwipeRight();
    void drawSwipeLeft();
    inline const uint8_t nextIndex() const { return (activeColor + 1) % 2; }
  };
}
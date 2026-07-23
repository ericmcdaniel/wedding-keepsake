#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"

namespace Apps::Animations
{
  class Swipe : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Swipe(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx} { wait(25); }
    void nextEvent() override;

    Lights::Color getSwipeColor();

  private:
    Platform::ContextManager &contextManager;
  };
}
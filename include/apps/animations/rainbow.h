#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"

namespace Apps::Animations
{
  class Rainbow : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Rainbow(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx} { wait(25); }
    void nextEvent() override;

    uint8_t colorPhaseShift = 0;
    Lights::Color getRainbowColor(uint8_t phase);

  private:
    Platform::ContextManager &contextManager;
  };
}
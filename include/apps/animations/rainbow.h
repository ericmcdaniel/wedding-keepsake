#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"
#include "utility/entropy.h"

namespace Apps::Animations
{
  class Rainbow : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Rainbow(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      wait(25);
      colorPhaseShift = (ctx.entropy.random() / 43) * 6;
    }
    void nextEvent() override;

    uint8_t colorPhaseShift;
    Lights::Color getRainbowColor();

  private:
    Platform::ContextManager &contextManager;
  };
}
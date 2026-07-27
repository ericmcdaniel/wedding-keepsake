#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"

namespace Apps::Animations
{
  class Candle : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Candle(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      ctx.renderer.clearDisplay();
      wait(idleTime);
    }
    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;

    static constexpr uint32_t candlePattern[] = {
        0xffffff, 0x9f9f50, 0x000000, 0x000030, 0xff8000, 0x202000, 0x000000, 0x000000,
        0xffffff, 0xbfbf80, 0x000030, 0xff0000, 0xff5000, 0xffa850, 0x404000, 0x000000,
        0xffffff, 0xbfbf80, 0x000030, 0xff0000, 0xff9000, 0xffa850, 0xffa020, 0x404000,
        0xffffff, 0x9f9f50, 0x000000, 0x000030, 0xff8000, 0x505000, 0x000000, 0x000000};

    uint8_t animationState = 0;
    static constexpr uint32_t idleTime = 100;
  };

}

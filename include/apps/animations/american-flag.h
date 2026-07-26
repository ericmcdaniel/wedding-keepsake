#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"

namespace Apps::Animations
{
  class AmericanFlag : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    AmericanFlag(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      ctx.renderer.clear();
    }
    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;

    static constexpr uint32_t flagPattern[] = {
        0x0000c0, 0x0000c0, 0x0000c0, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
        0x0000c0, 0x0000c0, 0x0000c0, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000,
        0x0000c0, 0x0000c0, 0x0000c0, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
        0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000};
    static constexpr uint8_t waveAmplitude = 128; // 0 - 255 Max
    static constexpr uint8_t waveTable[16] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 70, 60, 50, 40, 30, 20, 10};
    uint8_t wavePhase = 0;
    uint32_t lastWaveUpdate = 0;
  };

}

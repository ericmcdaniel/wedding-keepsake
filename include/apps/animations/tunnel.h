#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"

namespace Apps::Animations
{
  class Tunnel : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Tunnel(Platform::ContextManager *ctx) : Engine::Timer{&(ctx->time)}, contextManager{ctx} { wait(25); }
    void nextEvent() override;

    uint8_t colorPhaseShift = 0;
    Lights::Color getTunnelColor(uint8_t phase);

  private:
    Platform::ContextManager *contextManager;
  };
}
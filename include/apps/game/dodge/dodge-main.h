#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"

namespace Apps::Game
{
  class DodgeMain : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    DodgeMain(Platform::ContextManager *ctx) : contextManager{ctx} { wait(20); }
    void nextEvent() override;

  private:
    Platform::ContextManager *contextManager;
  };
}
#pragma once

#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "platform/context-manager.h"

namespace Apps::Animations
{
  class Rainbow : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    Rainbow(Platform::ContextManager *ctx) : contextManager{ctx} {}
    void nextEvent() override {}

  private:
    Platform::ContextManager *contextManager;
  };
}
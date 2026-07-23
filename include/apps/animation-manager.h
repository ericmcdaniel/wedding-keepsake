#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "apps/animations/rainbow.h"
#include "logger.h"

namespace Apps
{
  class AnimationManager : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    AnimationManager(Platform::ContextManager *ctx) : contextManager{ctx}
    {
      currentAnimation = new Apps::Animations::Rainbow{contextManager};
      log("Initializing AnimationManager, starting with Rainbow.");
    }

    ~AnimationManager()
    {
      delete currentAnimation;
      currentAnimation = nullptr;
    }

    void nextEvent() override;

  private:
    enum class AnimationRegistry
    {
      Rainbow,
      Tunnel
    };

    Platform::ContextManager *contextManager;
    Engine::ApplicationRuntime *currentAnimation = nullptr;
    AnimationRegistry state = AnimationRegistry::Rainbow;
    void nextAnimation();
  };
}
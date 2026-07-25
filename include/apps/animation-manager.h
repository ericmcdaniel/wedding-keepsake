#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "apps/animations/rainbow.h"
#include "utility/logger.h"

namespace Apps
{
  enum class AnimationRegistry
  {
    Rainbow,
    Tunnel,
    Swipe,
    COUNT
  };

  class AnimationManager : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    AnimationManager(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      nextAnimation();
      log("Initializing AnimationManager, starting with Rainbow.");
    }

    ~AnimationManager()
    {
      delete currentAnimation;
      currentAnimation = nullptr;
    }

    void nextEvent() override;

  private:
    Platform::ContextManager &contextManager;
    Engine::ApplicationRuntime *currentAnimation = nullptr;
    AnimationRegistry state = AnimationRegistry::Tunnel;
    void nextAnimation();
  };
}
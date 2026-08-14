#pragma once

#include "platform/context-manager.h"
#include "engine/application-runtime.h"
#include "engine/timer.h"
#include "apps/animations/rainbow.h"
#include "utilities/logger.h"
#include <EEPROM.h>

namespace Apps
{
  enum class AnimationRegistry
  {
    Tunnel,
    Swipe,
    Rainbow,
    AmericanFlag,
    Candle,
    COUNT
  };

  class AnimationManager : public Engine::ApplicationRuntime, public Engine::Timer
  {
  public:
    AnimationManager(Platform::ContextManager &ctx) : Engine::Timer{ctx.time}, contextManager{ctx}
    {
      uint8_t ct = static_cast<uint8_t>(AnimationRegistry::COUNT);
      uint8_t currentAnimation = 0;
      EEPROM.get(8, currentAnimation);
      state = static_cast<AnimationRegistry>((currentAnimation + static_cast<uint8_t>(ct) - 1) % ct);
      nextAnimation();
      log("Initializing AnimationManager, starting with Tunnel.");
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
    AnimationRegistry state; // = static_cast<AnimationRegistry>(static_cast<uint8_t>(AnimationRegistry::COUNT) - 2);
    void nextAnimation();
  };
}
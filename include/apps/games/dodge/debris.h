#pragma once

#include "apps/games/dodge/location.h"
#include "platform/context-manager.h"
#include "user/entity.h"
#include "engine/timer.h"

namespace Apps::Game::Dodge
{
  class Debris : public User::Entity, public Engine::Timer
  {
  public:
    Debris(Platform::ContextManager &ctx) : User::Entity(defaultTexture, topPosition),
                                            Engine::Timer{ctx.time},
                                            contextManager{ctx} {}
    void updatePosition();
    bool isActive() const { return active; }
    void activate(uint32_t speed);
    void deactivate();
    void reset();
    void render();

    bool completedCycle = false;
    static constexpr int8_t width = 4;
    static constexpr int8_t height = 2;
    static constexpr uint32_t orangePalette[] = {0x000000, 0xff7f00, 0xff7f00, 0x000000, 0x000000, 0xff7f00, 0xff7f00, 0x000000};
    static constexpr uint32_t redPalette[] = {0x000000, 0xb50000, 0xb50000, 0x000000, 0x000000, 0xb50000, 0xb50000, 0x000000};
    static constexpr uint32_t greenPalette[] = {0x000000, 0x00a910, 0x00a910, 0x000000, 0x000000, 0x00a910, 0x00a910, 0x000000};
    static constexpr User::Texture defaultTexture{width, height, orangePalette};
    static constexpr User::Point topPosition{6, 0};
    static constexpr User::Point bottomPosition{6, 2};

  private:
    Platform::ContextManager &contextManager;

    bool active = false;
    uint32_t speed = 0;
    uint32_t respawnTime = 1000;
    // bool impacted = false;
  };
}
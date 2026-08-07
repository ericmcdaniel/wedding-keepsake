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
    Debris(Platform::ContextManager &ctx) : User::Entity(defaultTexture, defaultPosition),
                                            Engine::Timer{ctx.time},
                                            contextManager{ctx}
    {
      reset();
    }
    const Location getLocation() const { return location; }
    // int8_t getPosition() const { return position; }
    void updatePosition();
    bool isActive() const { return active; }
    void activate(uint8_t speed);
    void deactivate();
    void reset();
    void render();

    bool completedCycle = false;

  private:
    Platform::ContextManager &contextManager;
    Location location = Location::Bottom;
    static constexpr int8_t width = 4;
    static constexpr int8_t height = 2;
    static constexpr uint32_t texture[] = {0x000000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000};
    static constexpr User::Texture defaultTexture{width, height, texture};
    static constexpr User::Point defaultPosition{6, 0};

    bool active;
    uint32_t lastRespawnTime = 0;
    uint32_t respawnTime = 1000;
    uint8_t speed;

    // bool impacted = false;
  };
}
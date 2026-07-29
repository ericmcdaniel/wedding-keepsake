#pragma once

#include "platform/context-manager.h"
#include "user/entity.h"
#include "apps/games/dodge/location.h"
#include "engine/timer.h"

namespace Apps::Game::Dodge
{

  class Player : public User::Entity
  {
  public:
    Player(Platform::ContextManager &ctx) : User::Entity(defaultTexture, defaultPosition), contextManager{ctx}, timer{ctx.time} {}

    void dodge();
    void render();
    Location getLocation() const { return location; }

    static constexpr int8_t width = 2;
    static constexpr int8_t height = 2;
    static constexpr uint32_t texture[] = {0xffffff, 0xffffff, 0xffffff, 0xffffff};
    static constexpr User::Texture defaultTexture{width, height, texture};
    static constexpr User::Point defaultPosition{8, -2};

  private:
    Platform::ContextManager &contextManager;
    Engine::Timer timer;
    Location location = Location::Bottom;
  };
}

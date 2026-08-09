#pragma once

#include "platform/context-manager.h"
#include "user/entity.h"
#include "apps/games/dodge/location.h"
#include "apps/games/dodge/debris.h"
#include "engine/timer.h"

namespace Apps::Game::Dodge
{
  enum class TextureState
  {
    Forward_1,
    Forward_2,
    Forward_3
  };

  class Player : public User::Entity
  {
  public:
    Player(Platform::ContextManager &ctx) : User::Entity(defaultTexture, defaultPosition),
                                            contextManager{ctx},
                                            textureTimer{ctx.time} {}

    void update();
    bool intersects(const Debris &debris) const;
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
    Engine::Timer textureTimer;
    Location location = Location::Bottom;
  };
}

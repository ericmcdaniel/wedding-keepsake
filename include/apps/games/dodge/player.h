#pragma once

#include "platform/context-manager.h"
#include "user/entity.h"

namespace Apps::Game::Dodge
{
  class Player : public User::Entity
  {
  public:
    Player(Platform::ContextManager &ctx) : User::Entity(defaultTexture, defaultPosition), contextManager{ctx} {}

    // void update(uint32_t deltaTime) override {}
    void render();

    static constexpr int8_t width = 3;
    static constexpr int8_t height = 2;
    static constexpr uint32_t texture[] = {0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000};
    static constexpr User::Texture defaultTexture{width, height, texture};
    static constexpr User::Point defaultPosition{3, 1};

  private:
    Platform::ContextManager &contextManager;
  };
}
#pragma once

#include "apps/games/dodge/location.h"
#include "platform/context-manager.h"
#include "user/entity.h"

namespace Apps::Game::Dodge
{
  class Debris : public User::Entity
  {
  public:
    Debris(Platform::ContextManager &ctx) : User::Entity(defaultTexture, defaultPosition), contextManager{ctx} { reset(); }
    const Location getLocation() const { return location; }
    // int8_t getPosition() const { return position; }
    void updatePosition();
    bool isActive() const { return active; }
    void activate(int8_t speed);
    void deactivate() { active = false; };
    void reset();
    void render();

  private:
    Platform::ContextManager &contextManager;
    Location location = Location::Bottom;
    static constexpr int8_t width = 2;
    static constexpr int8_t height = 2;
    static constexpr uint32_t texture[] = {0xff0000, 0xff0000, 0xff0000, 0xff0000};
    static constexpr User::Texture defaultTexture{width, height, texture};
    static constexpr User::Point defaultPosition{8, 0};

    bool active;
    int8_t speed;
    // int8_t position;
    bool completedCycle = false;

    // bool impacted = false;
  };
}
#pragma once

#include "platform/context-manager.h"
#include "apps/games/dodge/debris.h"
#include "apps/games/dodge/player.h"

namespace Apps::Game::Dodge
{
  class DebrisManager : public Engine::Timer
  {
  public:
    DebrisManager(Platform::ContextManager &ctx) : Engine::Timer{ctx.time},
                                                   contextManager{ctx},
                                                   debrisPool{ctx, ctx} {}
    DebrisManager(const DebrisManager &) = delete;
    DebrisManager &operator=(const DebrisManager &) = delete;

    Debris &operator[](uint16_t index) { return debrisPool[index]; }
    const Debris &operator[](uint16_t index) const { return debrisPool[index]; }

    auto begin() { return debrisPool[0]; }
    auto end() { return debrisPool[_size - 1]; }
    const auto begin() const { return debrisPool[0]; }
    const auto end() const { return debrisPool[_size - 1]; }

    const uint8_t size() const;

    void updatePositions();
    void dispatch(uint32_t speed);
    bool checkCollision(const Player &player);
    void render();
    void reset();

  private:
    Platform::ContextManager &contextManager;
    static constexpr uint8_t _size = 2;
    Debris debrisPool[_size];
  };
}
#pragma once

#include <stdint.h>

namespace Apps::Game::Dodge
{
  struct LevelConfig
  {
    uint32_t debrisSpeed;     // slow=400, fast=150
    uint32_t debrisRespawn;   // slow=3000, fast=1000
    uint32_t backgroundSpeed; // slow=361, fast=80
  };

  class LevelManager
  {
  public:
    const LevelConfig &operator[](uint16_t index) const { return levelConfig[index]; }
    static constexpr uint8_t size = 5;

  private:
    static constexpr LevelConfig levelConfig[size] = {
        {.debrisSpeed = 400, .debrisRespawn = 3000, .backgroundSpeed = 361},
        {.debrisSpeed = 170, .debrisRespawn = 3000, .backgroundSpeed = 113},
        {.debrisSpeed = 350, .debrisRespawn = 1650, .backgroundSpeed = 417},
        {.debrisSpeed = 170, .debrisRespawn = 1671, .backgroundSpeed = 80},
        {.debrisSpeed = 163, .debrisRespawn = 1013, .backgroundSpeed = 71}};
  };
}

/*
  Some level ideas:
  - slow, sparce { debrisSpeed=400, debrisReswapnDelay=3000, backgroundRenderRate=361 }
  - fast, sparce
  - slow, dense { debrisSpeed=400, debrisReswapnDelay=1650 }
*/
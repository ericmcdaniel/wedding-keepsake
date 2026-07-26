#pragma once

#include "user/point.h"
#include "user/texture.h"
#include "engine/renderer.h"

namespace User
{
  class Entity
  {
  public:
    virtual ~Entity() = default;

    virtual void update(uint32_t deltaTime) = 0;

    bool intersects(const Entity &other) const;

  protected:
    Point position;
  };
}
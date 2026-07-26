#pragma once

#include "user/point.h"
#include "user/texture.h"
#include "engine/renderer.h"

namespace User
{
  class Entity
  {
  public:
    Entity(const Texture &t, const Point &p) : texture{t}, position{p} {}
    virtual ~Entity() = default;

    // virtual void update(uint32_t deltaTime) = 0;

    bool intersects(const Entity &other) const
    {
      if (position.x + texture.width > other.position.x)
        return true;
      return false; // TODO: finish
    }

  protected:
    Point position;
    Texture texture;
  };
}
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

    Point position;
    Texture texture;
  };
}
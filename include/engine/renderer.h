#pragma once

#include "lights/led-matrix.h"

namespace Engine
{
  class Renderer
  {
  public:
    Renderer() = default;

    Lights::LedMatrix leds;

    // void drawPixel(const RenderModel &renderModel, const uint16_t offset);
    // void renderEntity(const RenderModel &model);

  private:
    // void blend(const RenderModel &renderModel, const uint16_t offset);
  };
}
#pragma once

#include "core/context-manager.h"

namespace Engine
{
  class GameEngine
  {
  public:
    GameEngine();

    void runApplication();

  private:
    SystemCore::ContextManager contextManager;
    uint32_t lastRender = 0;

    void initializeEngine();
    void renderLedMatrix();
  };
}
#pragma once

#include "platform/context-manager.h"

namespace Engine
{
  class GameEngine
  {
  public:
    GameEngine();

    void initializeEngine();
    void runApplication();

  private:
    Platform::ContextManager contextManager;
    void renderFrame();
  };
}
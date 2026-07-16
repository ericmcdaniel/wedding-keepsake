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

    uint32_t lastRender = 0;
    uint32_t lastFrame = 0;
    uint8_t activeRow = 0;
    static constexpr uint32_t rowRefreshRate = 4166;    // 1/4 of 60Hz, as each row is multiplexed
    static constexpr uint32_t frameRefreshRate = 16666; // 60Hz

    void renderFrameRow();
    inline void disableActiveRow();
    inline void enableActiveRow();
    inline void setNextRow();
  };
}
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
    uint8_t bamBitPlane = 0;
    uint8_t bamCounter = 0;
    static constexpr uint32_t rowRefreshRate = 4;    // 1/4 of 60Hz, as each row is multiplexed
    static constexpr uint32_t frameRefreshRate = 16; // 60Hz, to keep multiplexer in sync

    static constexpr uint8_t bamDurations[8] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128};
    static constexpr uint8_t rowMask = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

    void renderFrameRow();
    inline void disableActiveRow();
    inline void enableActiveRow();
    inline void setNextRow();
    void shiftOutByte(uint8_t value);
  };
}
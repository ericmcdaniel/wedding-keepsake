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

    uint32_t lastFullFrameRender = 0;
    uint32_t lastMatrixRowRender = 0;
    uint8_t activeRow = 0;
    uint8_t bamBitPlane = 0;
    uint8_t bamCounter = 0;
    static constexpr uint32_t rowRefreshRate = 50;      // Leave multiplexed row on for 50us minimum.
    static constexpr uint32_t frameRefreshRate = 16666; // Refresh full frame at 60 Hz (16.6 ms)
    static constexpr uint8_t rowMask = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

    // completely arbitrary values, but iterating from 0-5 leads to choppy display. This is
    // a symptom of how BOM works. this 6-bit array mixes up long PWM durations with short onces, making it look more natural.
    static constexpr uint8_t bamSequence[6] = {5, 0, 4, 1, 3, 2};

    void renderFrameRow(uint32_t currentTime);
    inline void disableActiveRow();
    inline void enableActiveRow();
    inline void selectNextMatrixRow();
    void pwmAdjustAndShiftToLeds();
    inline void toggleLatch();
    void shiftOutByte(uint8_t value);
    inline void shiftBamBit();
    inline uint8_t reduceTo6Bit(uint8_t value);
  };
}
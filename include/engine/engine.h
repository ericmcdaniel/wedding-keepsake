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
    uint32_t lastColorActivation = 0;
    uint8_t activeRow = 0;
    uint8_t bamBitPlane = 0;
    uint8_t bamCounter = 0;
    static constexpr uint32_t rowRefreshRate = 44;      // 1/4 of 60Hz, as each row is multiplexed
    static constexpr uint32_t frameRefreshRate = 16666; // 60Hz, to keep multiplexer in sync
    static constexpr uint8_t rowMask = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

    Lights::Color colorArray[16] = {
        Lights::Color{31, 0, 0},
        Lights::Color{0, 31, 0},
        Lights::Color{0, 0, 31},
        Lights::Color{31, 31, 31},
        Lights::Color{63, 0, 0},
        Lights::Color{0, 63, 0},
        Lights::Color{0, 0, 63},
        Lights::Color{63, 63, 63},
        Lights::Color{127, 0, 0},
        Lights::Color{0, 127, 0},
        Lights::Color{0, 0, 127},
        Lights::Color{127, 127, 127},
        Lights::Color{255, 0, 0},
        Lights::Color{0, 255, 0},
        Lights::Color{0, 0, 255},
        Lights::Color{255, 255, 255}};
    uint8_t colorIdx = 0;

    void renderFrameRow();
    inline void disableActiveRow();
    inline void enableActiveRow();
    inline void setNextRow();
    void shiftOutByte(uint8_t value);
    inline void shiftBamBit();
  };
}
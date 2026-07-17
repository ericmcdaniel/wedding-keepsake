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
    static constexpr uint32_t rowRefreshRate = 50;      // 1/4 of 60Hz, as each row is multiplexed
    static constexpr uint32_t frameRefreshRate = 16666; // 60Hz, to keep multiplexer in sync
    static constexpr uint8_t rowMask = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

    Lights::Color colorArray[20] = {
        Lights::Color{15, 0, 0},
        Lights::Color{31, 0, 0},
        Lights::Color{85, 0, 0},
        Lights::Color{170, 0, 0},
        Lights::Color{255, 0, 0},
        Lights::Color{0, 15, 0},
        Lights::Color{0, 31, 0},
        Lights::Color{0, 85, 0},
        Lights::Color{0, 170, 0},
        Lights::Color{0, 255, 0},
        Lights::Color{0, 0, 15},
        Lights::Color{0, 0, 31},
        Lights::Color{0, 0, 85},
        Lights::Color{0, 0, 170},
        Lights::Color{0, 0, 255},
        Lights::Color{15, 15, 15},
        Lights::Color{31, 31, 31},
        Lights::Color{85, 85, 85},
        Lights::Color{170, 170, 170},
        Lights::Color{255, 255, 255}};
    uint8_t colorIdx = 0;
    static constexpr uint8_t bamSequence[8] =
        {7,
         3,
         5,
         1,
         6,
         2,
         4,
         0};

    void renderFrameRow();
    inline void disableActiveRow();
    inline void enableActiveRow();
    inline void setNextRow();
    void shiftOutByte(uint8_t value);
    inline void shiftBamBit();
  };
}
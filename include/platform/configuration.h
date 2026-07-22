#pragma once

#include <Arduino.h>
#include "engine/state-manager.h"

namespace Platform
{
  class Configuration
  {
  public:
    static constexpr uint16_t numLeds = 32;
    static constexpr uint16_t numRows = 4;
    static constexpr uint16_t numColumns = 8;
    static constexpr uint32_t serialBaud = 115200;

    // static constexpr uint8_t shiftRegisterDataPin = PIN_PA1;
    static constexpr uint8_t buttonPin = PIN0_bm;
    static constexpr uint8_t rowPins[] = {
        PIN_PA4,
        PIN_PA5,
        PIN_PA6,
        PIN_PA7};

    inline static Engine::SystemState &startupState() { return _startupState; };

    static void load();

  private:
    inline static Engine::SystemState _startupState = Engine::SystemState::Animation;
    static_assert((Platform::Configuration::numColumns & (Platform::Configuration::numColumns - 1)) == 0, "numColumns must be a power of two");
    static_assert((Platform::Configuration::numRows & (Platform::Configuration::numRows - 1)) == 0, "numRows must be a power of two");
  };
}
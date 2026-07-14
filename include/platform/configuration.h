#pragma once

#include <Arduino.h>
#include "engine/state-manager.h"

namespace Platform
{
  class Configuration
  {
  public:
    static constexpr uint16_t numLeds = 32;
    static constexpr uint32_t serialBaud = 115200;
    static Engine::SystemState &startupState() { return _startupState; };

    static void load();

  private:
    inline static Engine::SystemState _startupState = Engine::SystemState::Initialize;
  };
}
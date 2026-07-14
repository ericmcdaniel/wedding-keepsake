#pragma once

#include <EEPROM.h>
#include "engine/application-runtime.h"

namespace Platform
{
  class ContextManager
  {
  public:
    ContextManager() {} // : display{this}, stateManager{this}
    ~ContextManager();
    ContextManager(ContextManager &&other) = delete;
    ContextManager(const ContextManager &other) = delete;

    Engine::ApplicationRuntime *application = nullptr;
  };
}
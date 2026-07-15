#pragma once

#include <EEPROM.h>
#include "engine/application-runtime.h"
#include "engine/state-manager.h"
#include "engine/renderer.h"
#include "user/controller.h"

namespace Platform
{
  class ContextManager
  {
  public:
    ContextManager() : stateManager{this} {}
    ~ContextManager();
    ContextManager(ContextManager &&other) = delete;
    ContextManager(const ContextManager &other) = delete;

    Engine::ApplicationRuntime *application = nullptr;
    Engine::StateManager stateManager;
    Engine::Renderer renderer;
    User::Controller controller;

    void initializeSystemMemory();
  };
}
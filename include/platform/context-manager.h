#pragma once

#include <EEPROM.h>
#include "engine/application-runtime.h"
#include "engine/state-manager.h"
#include "engine/renderer.h"
// #include "engine/marquee.h"
#include "user/button.h"
#include "platform/time.h"
#include "utilities/entropy.h"

namespace Platform
{

  class ContextManager
  {
  public:
    ContextManager() : stateManager{*this}, entropy{time} {}
    ~ContextManager();
    ContextManager(ContextManager &&other) = delete;
    ContextManager(const ContextManager &other) = delete;

    Time time;
    Engine::ApplicationRuntime *application = nullptr;
    Engine::StateManager stateManager;
    Engine::Renderer renderer;
    // Engine::Marquee marquee;
    User::Button button;
    Utilities::Entropy entropy;

    void initializeSystemMemory();
    void changeApplication(Engine::SystemState nextState);
  };
}
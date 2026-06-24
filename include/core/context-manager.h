#pragma once

#include "engine/layer.h"
#include "engine/state-manager.h"
#include "lights/led-matrix.h"

namespace SystemCore
{
  class ContextManager
  {
  public:
    ContextManager();
    ~ContextManager();
    ContextManager(ContextManager &&other) = delete;
    ContextManager(const ContextManager &other) = delete;

    Engine::Layer *application = nullptr;
    Engine::StateManager stateManager;
    Lights::LedMatrix leds;

    void initializeSystemMemory();
    void navigateMainMenu();
    void navigateGameMenu();
    void navigateSceneMenu();
    void checkExitRequest();
    void checkDisplayVisibilityChange();
    void transitionLayer();
  };
}
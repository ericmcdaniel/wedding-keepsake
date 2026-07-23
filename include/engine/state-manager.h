#pragma once

namespace Platform
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Engine
{
  enum class SystemState
  {
    Animation,
    Game,
    Error
  };

  class StateManager
  {
  public:
    StateManager(Platform::ContextManager &ctx) : contextManager{ctx},
                                                  systemState{SystemState::Animation} {}

    bool isRunning() const { return systemState != SystemState::Error; }
    const SystemState current() const { return systemState; }
    void setNext(SystemState currentState) { systemState = currentState; };

  private:
    Platform::ContextManager &contextManager;
    SystemState systemState;
  };
}
#pragma once

namespace SystemCore
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Engine
{
  enum class SystemState
  {
    Initialize,
    Home,
    Error
  };

  class StateManager
  {
  public:
    StateManager(SystemCore::ContextManager *ctx) : contextManager{ctx},
                                                    systemState{SystemState::Initialize} {}

    bool isRunning() const { return systemState != SystemState::Error; }
    const SystemState current() const { return systemState; }
    void setNext(SystemState state);

  private:
    SystemCore::ContextManager *contextManager;
    SystemState systemState;
  };
}
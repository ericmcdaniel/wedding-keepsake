#include "platform/context-manager.h"
#include "platform/configuration.h"

namespace Platform
{
  ContextManager::~ContextManager()
  {
    if (application)
    {
      delete application;
      application = nullptr;
    }
  }

  void ContextManager::initializeSystemMemory()
  {
    Configuration::load();
    stateManager.setNext(Configuration::startupState());
  }
}
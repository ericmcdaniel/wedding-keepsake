#include "platform/context-manager.h"

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
}
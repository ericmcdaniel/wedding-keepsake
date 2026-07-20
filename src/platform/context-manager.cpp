#include "platform/context-manager.h"
#include "platform/configuration.h"
#include "apps/animations/rainbow.h"
#include "logger.h"

using namespace Platform;

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

void ContextManager::changeApplication()
{
  if (application)
  {
    delete application;
    application = nullptr;
  }
  switch (stateManager.current())
  {
  case Engine::SystemState::Animation:
    application = new Apps::Animations::Rainbow{this};
    logf("Transitioning to Rainbow (Animation)");
    break;
  }
}
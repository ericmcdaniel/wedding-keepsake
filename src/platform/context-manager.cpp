#include "platform/context-manager.h"
#include "platform/configuration.h"
#include "apps/animation-manager.h"
#include "apps/game-manager.h"
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
    application = new Apps::AnimationManager{this};
    logf("Transitioning to Animations");
    break;
  case Engine::SystemState::Game:
    application = new Apps::GameManager{this};
    logf("Transitioning to Games (Temporary Placeholder)");
    break;
  }
}

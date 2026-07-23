#include "apps/animation-manager.h"
#include "logger.h"

using namespace Apps;

void AnimationManager::nextEvent()
{
  if (contextManager->button.wasSinglePress())
  {
    nextAnimation();
  }
  currentAnimation->nextEvent();
}

void AnimationManager::nextAnimation()
{
  log("Next animation was requested, but only one exists.");
}
#include "apps/animation-manager.h"
#include "apps/animations/rainbow.h"
#include "apps/animations/tunnel.h"
#include "apps/animations/swipe.h"
#include "utilities/logger.h"
#include "utilities/common.h"

using namespace Apps;

void AnimationManager::nextEvent()
{
  if (contextManager.button.wasSinglePress())
  {
    nextAnimation();
  }
  currentAnimation->nextEvent();
}

void AnimationManager::nextAnimation()
{

  if (currentAnimation)
  {
    delete currentAnimation;
    currentAnimation = nullptr;
  }

  Utilities::advance(state);

  switch (state)
  {
  case AnimationRegistry::Tunnel:
    currentAnimation = new Apps::Animations::Tunnel{contextManager};
    state = AnimationRegistry::Tunnel;
    logf("Animation: Tunnel");
    break;

  case AnimationRegistry::Swipe:
    currentAnimation = new Apps::Animations::Swipe{contextManager};
    state = AnimationRegistry::Swipe;
    logf("Animation: Swipe");
    break;

  case AnimationRegistry::Rainbow:
    currentAnimation = new Apps::Animations::Rainbow{contextManager};
    state = AnimationRegistry::Rainbow;
    logf("Animation: Rainbow");
    break;
  }
}
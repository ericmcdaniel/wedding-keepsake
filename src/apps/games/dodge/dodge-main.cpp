#include "apps/games/dodge/dodge-main.h"
#include "engine/state-manager.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void Main::nextEvent()
{
  contextManager.renderer.clearDisplay();
  switch (state)
  {
  case State::BeginGame:
    prepareUser();
    render();
    break;
  case State::Playing:
    nextUpdate();
    assessDifficulty();
    checkCollisions();
    render();
    break;
  case State::CollisionMuzzleFlash:
    renderMuzzleFlash();
    break;
  case State::GameOver:
    render();
    break;
  }
}

void Main::prepareUser()
{
  if (isReady())
  {
    if (player.position.x <= 1) // start game
    {
      state = State::Playing;
      contextManager.button.reset();
      // wait(debrisRespawnDelay / 3);
      return;
    }

    playAnimationSequence();
    wait(startDeplayTime);
  }
}

/*
  I kindasorta micro-optimized this function, but this really just amounts to a scrolling
  display that has colors fade out, slanted, and animate movement to the left.
  Looks like:
      // // // / / /        // // // / / /
     // // // / / /        // // // / / /    <--- Scrolling to the left
    // // // / / /        // // // / / /
   // // // / / /        // // // / / /
*/
void Main::handleBackground()
{
#if 1
  // diagonal
  constexpr uint8_t waveFactorsBlue[] = {48, 30, 12, 12, 0, 0, 0, 0};
  constexpr uint8_t waveFactorsGreen[] = {12, 0, 0, 0, 0, 0, 0, 0};
  static uint8_t offset = 3;
  Lights::Color color;

  for (uint8_t i = 0; i < Platform::Configuration::numColumns; i++)
  {
    uint8_t factorBlue = waveFactorsBlue[(offset + i) % backgroundRepeatLength];
    uint8_t factorGreen = waveFactorsGreen[(offset + i) % backgroundRepeatLength];
    color = {0, factorGreen, factorBlue};

    for (uint8_t j = 0; j < Platform::Configuration::numRows; j++)
    {
      uint8_t rowShift = Platform::Configuration::numRows - j - 1;
      if (player.getLocation() == Location::Top || player.getLocation() == Location::TransitioningUp)
      {
        rowShift = j;
      }
      contextManager.renderer.renderPixel(color, (i + rowShift) % Platform::Configuration::numColumns, j);
    }
  }

  if (backgroundTimer.isReady())
  {
    backgroundTimer.wait(backgroundRenderRate);
    offset++;
    if (offset >= backgroundRepeatLength)
    {
      offset = 0;
    }
  }

#else
  constexpr uint8_t waveFactors[] = {48, 30, 12, 12, 0, 0, 0};
  static uint8_t offset = 0;
  Lights::Color color;

  for (uint8_t i = 0; i < Platform::Configuration::numColumns; i++)
  {
    uint8_t factor = waveFactors[(offset + i) % 7];
    color = {0, factor / 4, factor};
    contextManager.renderer.renderVerticalLine(color, i, 0, 3);
  }

  if (backgroundTimer.isReady())
  {
    backgroundTimer.wait(backgroundRenderRate);
    offset++;
    if (offset >= 7)
    {
      offset = 0;
    }
  }
#endif
}

void Main::nextUpdate()
{
  player.update();
  if (contextManager.button.wasDoublePress() || contextManager.button.wasSinglePress())
  {
    player.dodge();
  }
  debrisManager.updatePositions();
}

void Main::assessDifficulty()
{
  if (isReady())
  {
    // if (windDownTimer.isReady())
    // {
    //   state.current = Actions::WindDown;
    // }

    if (state == State::Playing)
    {
      debrisManager.dispatch(debrisSpeed);
      // uint32_t timeDelay = static_cast<uint32_t>((esp_random() % static_cast<uint32_t>(interval)) + gap);
      wait(debrisRespawnDelay);
    }

    // bool shouldStartNextRound = state.current == Actions::WindDown && flareManager.size() == 2;
    // if (shouldStartNextRound)
    // {
    //   windDownTimer.wait(windDownLength);
    //   state.current = Actions::ActiveGame;
    //   speed *= 1.07;
    //   interval *= 0.8;
    //   gap *= 0.82;
    // }
  }
}

void Main::checkCollisions()
{
  if (debrisManager.checkCollision(player))
  {
    state = State::CollisionMuzzleFlash;
    backgroundTimer.disable();
    wait(25);
    log("Collision with debris");
  }
}

void Main::playAnimationSequence()
{
  uint8_t offset = 1;
  if (player.position.y >= 2)
  {
    offset = 0;
  }
  player.position.move(-1, offset);
}

void Main::render()
{
  handleBackground();
  debrisManager.render();
  player.render();
}

void Main::renderMuzzleFlash()
{
  static uint8_t flashCount = 0;

  if (isReady())
  {
    flashCount++;
    if (flashCount >= 5)
    {
      flashCount = 0;
      state = State::GameOver;
      return;
    }

    switch (flashCount)
    {
    case 1:
      contextManager.renderer.renderFullCanvas(0xffffff);
      break;
    case 0:
    case 2:
    case 4:
      contextManager.renderer.renderFullCanvas(0x000000);
      break;
    case 3:
      contextManager.renderer.renderFullCanvas(0xff0000);
      break;
    }

    wait(25);
  }
}
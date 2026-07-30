#include "apps/games/dodge/dodge-main.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void Main::nextEvent()
{
  contextManager.renderer.clearDisplay();
  switch (state)
  {
  case State::BeginGame:
    handleStartup();
    break;
  case State::Playing:
    handleGamePlay();
    updateDebrisPositions();
    break;
  }

  render();

  // if (isReady())
  // {
  //   wait(20);

  //   contextManager.renderer.clearDisplay();
  //   player.render();

  //   if (contextManager.button.wasDoublePress())
  //   {
  //     log("Double press fired.");
  //   }
  //   else if (contextManager.button.wasSinglePress())
  //   {
  //     log("Single press fired.");
  //   }
  // }
}

void Main::updateDebrisPositions()
{
  if (!debisPool[0].isActive())
    return; // continue;
  debisPool[0].updatePosition();
}

void Main::handleStartup()
{
  if (isReady())
  {
    wait(startDeplayTime);
    uint8_t offset = 1;
    if (player.position.y >= 2)
    {
      offset = 0;
    }
    if (player.position.x <= 0)
    {
      state = State::Playing;
      contextManager.button.reset();
    }
    else
    {
      player.position.move(-1, offset);
    }
  }
}

/*
  I kindasorta started microoptimizing, but this really just amounts to a srolling
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
  constexpr uint8_t waveFactors[] = {48, 30, 12, 12, 0, 0, 0, 0};
  static uint8_t offset = 3;
  Lights::Color color;

  for (uint8_t i = 0; i < Platform::Configuration::numColumns; i++)
  {
    uint8_t factor = waveFactors[(offset + i) % backgroundRepeatLength];
    color = {0, factor / 4, factor};

    for (uint8_t j = 0; j < Platform::Configuration::numRows; j++)
    {
      uint8_t rowShift = Platform::Configuration::numRows - j - 1;
      if (player.getLocation() == Location::Top)
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

void Main::handleGamePlay()
{
  if (contextManager.button.wasSinglePress())
  {
    player.dodge();
  }
}

void Main::render()
{
  handleBackground();
  player.render();
  debisPool[0].render();
}
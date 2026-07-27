#include "apps/games/dodge/dodge-main.h"
#include "utilities/logger.h"

using namespace Apps::Game::Dodge;

void Main::nextEvent()
{
  contextManager.renderer.clear();
  switch (state)
  {
  case State::BeginGame:
    drawStartup();
    break;
  case State::Playing:
    break;
  }

  render();

  // if (isReady())
  // {
  //   wait(20);

  //   contextManager.renderer.clear();
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

void Main::drawStartup()
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
    }
    else
    {
      player.position.move(-1, offset);
    }
  }
}

void Main::drawBackground()
{
  constexpr uint8_t vals[] = {48, 30, 12, 12, 0, 0, 0};

  static uint8_t offset = 0;

  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset) % 7]}, 0, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 1) % 7]}, 1, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 2) % 7]}, 2, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 3) % 7]}, 3, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 4) % 7]}, 4, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 5) % 7]}, 5, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 6) % 7]}, 6, 0, 3);
  contextManager.renderer.drawVerticalLine({0, 0, vals[(offset + 7) % 7]}, 7, 0, 3);

  if (backgroundTimer.isReady())
  {
    backgroundTimer.wait(backgroundRenderRate);
    offset++;
  }
}

void Main::render()
{
  drawBackground();
  player.render();
}
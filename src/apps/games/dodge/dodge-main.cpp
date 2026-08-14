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
  case State::Winddown:
    nextUpdate();
    assessDifficulty();
    checkCollisions();
    render();
    break;
  case State::CollisionMuzzleFlash:
    renderMuzzleFlash();
    break;
  case State::GameOver:
    checkContinue(State::DisplayScore);
    renderGameOver();
    break;
  case State::DisplayScore:
    checkContinue(State::GameOver);
    renderScore();
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
      // wait(levelManager[level].debrisRespawn / 3);
      return;
    }

    playAnimationSequence();
    wait(gameStartAnimationSpeed);
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
#ifdef USE_ANGLED_BACKGROUND
  // diagonal
  constexpr uint8_t waveFactorsBlue[] = {48, 30, 12, 12, 0, 0, 0, 0};
  constexpr uint8_t waveFactorsGreen[] = {12, 0, 0, 0, 0, 0, 0, 0};
  static uint8_t offset = 3;
  Lights::Color color;

  for (uint8_t i = 0; i < Platform::Configuration::numColumns; i++)
  {
    uint8_t factorBlue = waveFactorsBlue[(offset + i) % 8];
    uint8_t factorGreen = waveFactorsGreen[(offset + i) % 8];
    color = {0, factorGreen, factorBlue};

    for (uint8_t j = 0; j < Platform::Configuration::numRows; j++)
    {
      uint8_t rowShift = Platform::Configuration::numRows - j - 1;

      //
      // Taking this out because as much as I like the vision where it looks like it's
      // actually flying in a direction, it's a little too busy. The angle is now static.
      //
      // if (player.getLocation() == Location::Top || player.getLocation() == Location::TransitioningUp)
      // {
      //   rowShift = j;
      // }
      contextManager.renderer.renderPixel(color, (i + rowShift) % Platform::Configuration::numColumns, j);
    }
  }

  if (backgroundTimer.isReady())
  {
    backgroundTimer.wait(levelManager[level].backgroundSpeed);
    offset++;
    if (offset >= 8)
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
    backgroundTimer.wait(levelManager[level].backgroundSpeed);
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
    if (winddownTimer.isReady())
    {
      state = State::Winddown;
      wait(250);
    }

    if (state == State::Playing)
    {
      debrisManager.dispatch(levelManager[level].debrisSpeed);
      uint32_t randomExtraDelay = contextManager.entropy.random() % static_cast<uint32_t>(levelManager[level].debrisRespawn / 4);
      wait(levelManager[level].debrisRespawn + randomExtraDelay);
    }

    bool shouldStartNextRound = state == State::Winddown && debrisManager.size() == 0;
    if (shouldStartNextRound)
    {
      winddownTimer.wait(levelDuration);
      state = State::Playing;
      level = level % (LevelManager::size - 1) + 1;
    }
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

void Main::checkContinue(State s)
{
  if (contextManager.button.wasDoublePress())
  {
    reset();
    state = State::BeginGame;
  }

  if (contextManager.button.wasSinglePress())
  {
    state = s;
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

void Main::renderGameOver()
{
  static bool shouldDisplayDebris = false;
  handleBackground();

  debrisManager.render();
  if (shouldDisplayDebris)
  {
    player.render();
  }

  if (isReady())
  {
    shouldDisplayDebris = !shouldDisplayDebris;
    wait(500);
  }
}

void Main::renderScore()
{

  // this is really starting to look janky and below the quality I try to deliver, but
  // the deadline is here. I've ditched the scrolling marquee (for now) and just use the
  // grid itself to show the score.
  static bool isIlluminated = false;

  static constexpr uint32_t scoreColors[] = {0x0000ff, 0xff8a00, 0x00ff00, 0xff0000, 0x00ffff, 0xffff00};

  uint8_t scoreGrouping = (debrisManager.getScore() / 32) % 6;
  uint8_t highScoreGrouping = (debrisManager.getHighScore() / 32) % 6;
  uint32_t scoreColor = scoreColors[scoreGrouping];
  uint32_t highScoreColor = scoreColors[highScoreGrouping];

  // if (scoreTimer.isReady())
  // {

  for (uint8_t i = 0; i < debrisManager.getScore() % 32; ++i)
  {
    if (debrisManager.getScore() == debrisManager.getHighScore() && isIlluminated)
    {
      scoreColor = 0xffffff;
    }
    contextManager.renderer.renderPixel(scoreColor, i);
  }
  // if (scoreInc < debrisManager.getScore())
  // {
  //   scoreInc++;
  //   scoreTimer.wait(100);
  // }
  // }

  if ((debrisManager.getHighScore() % 32) > 0 && isIlluminated)
  {
    contextManager.renderer.renderPixel(0xffffff, (debrisManager.getHighScore() % 32) - 1);
  }
  else if ((debrisManager.getHighScore() % 32) > 0 && !isIlluminated)
  {
    contextManager.renderer.renderPixel(highScoreColor, (debrisManager.getHighScore() % 32) - 1);
  }

  if (isReady())
  {
    isIlluminated = !isIlluminated;
    wait(500);
  }
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

void Main::reset()
{
  player.reset();
  debrisManager.reset();
  state = State::BeginGame;
  level = 0;
  wait(750);
  backgroundTimer.enable(levelManager[level].backgroundSpeed);
  scoreInc = 0;
}
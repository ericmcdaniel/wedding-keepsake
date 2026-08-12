#include "apps/games/dodge/debris.h"
#include "platform/configuration.h"

using namespace Apps::Game::Dodge;

void Debris::updatePosition()
{
  if (isReady())
  {
    position.x -= 1;
    if (position.x <= -width)
    {
      deactivate();
    }
    wait(speed);
  }
}

int8_t Debris::nextPosition()
{
  uint32_t random = contextManager.entropy.random();
  const int8_t candidate = random % 2;

  // for the first run only
  if (lastPosition == -1)
  {
    lastPosition = candidate;
    repeatCount = 0;
    return lastPosition;
  }

  // new position, steak ends
  if (candidate != lastPosition)
  {
    lastPosition = candidate;
    repeatCount = 0;
    return lastPosition;
  }

  // We accomplish this by requiring an increasing number
  // of low bits to be zero.

  // repeat, so the streak started. I want a 50% probability from each previous time
  // it repeats. So 50% the first, 25% the second, 12.5% the third, 6.25% ..., etc
  const uint8_t bitsRequired = repeatCount + 1;

  // chatgpt threw me a bone with this optimizaiton: I can determine the probability in successive
  // order by checking the number of 1 of every position. Starting at the last index it's with 0 or 1 (50%)
  // But if/when it escalates to 2 (second to last index), both positions need to be 1, and that's 25%. Repeat.
  if (bitsRequired >= 32 || (random & ((1UL << bitsRequired) - 1)) != 0)
  {
    // reject, switch
    lastPosition = (lastPosition == 0) ? 1 : 0;
    repeatCount = 0;
  }
  else
  {
    // it beat the odds.
    repeatCount++;
  }

  return lastPosition;
}

void Debris::activate(uint32_t s)
{
  active = true;
  speed = s;
}

void Debris::deactivate()
{
  completedCycle = true;
  reset();
};

void Debris::reset()
{
  active = false;

  uint32_t randInt = contextManager.entropy.random();
  switch (randInt % 3)
  {
  case 0:
    texture = {width, height, orangePalette};
    break;
  case 1:
    texture = {width, height, redPalette};
    break;
  case 2:
    texture = {width, height, greenPalette};
    break;
  }

  int8_t next = nextPosition();
  if (next)
  {
    position = topPosition;
  }
  else
  {
    position = bottomPosition;
  }
}

void Debris::render()
{
  for (int8_t row = 0; row < height; row++)
  {
    for (int8_t col = 0; col < width; col++)
    {
      contextManager.renderer.renderPixel(texture.pixels[row * width + col], position.x + col, position.y + row);
    }
  }
}
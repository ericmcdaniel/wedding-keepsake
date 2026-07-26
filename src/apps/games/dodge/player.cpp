#include "apps/games/dodge/player.h"

using namespace Apps::Game::Dodge;

void Player::render()
{
  for (int8_t y = 0; y < height; y++)
  {
    for (int8_t x = 0; x < width; x++)
    {
      contextManager.renderer.drawPixel(texture[y * width + x], position.y + y, position.x + x);
    }
  }
}
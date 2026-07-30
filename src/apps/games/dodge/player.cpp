#include "apps/games/dodge/player.h"

using namespace Apps::Game::Dodge;

void Player::dodge()
{
  if (location == Location::Top)
  {
    position.move(0, 2);
    location = Location::Bottom;
  }
  else
  {
    position.move(0, -2);
    location = Location::Top;
  }
}

void Player::render()
{
  for (int8_t row = 0; row < height; row++)
  {
    for (int8_t col = 0; col < width; col++)
    {
      contextManager.renderer.renderPixel(texture[row * width + col], position.x + col, position.y + row);
    }
  }
}
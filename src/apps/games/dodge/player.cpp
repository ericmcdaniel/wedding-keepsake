#include "apps/games/dodge/player.h"

using namespace Apps::Game::Dodge;

void Player::dodge()
{
  if (location == Location::Top)
  {
    location = Location::TransitioningDown;
    position.move(0, 1);
  }

  if (location == Location::Bottom)
  {
    location = Location::TransitioningUp;
    position.move(0, -1);
  }

  textureTimer.wait(100);
}

void Player::update()
{
  if (textureTimer.isReady())
  {
    switch (location)
    {
    case Location::TransitioningDown:
      position.move(0, 1);
      location = Location::Bottom;
      break;
    case Location::TransitioningUp:
      position.move(0, -1);
      location = Location::Top;
      break;
    };
  }
}

bool Player::intersects(const Debris &debris) const
{
  return (
      (position.y - debris.position.y <= 1)        // on the same line (change 0 to -1 if including transition state, makes it harder)
      && (position.x >= debris.position.x)         // within the hit box (user's right, debris's left)
      && (position.x - width <= debris.position.x) // within the hit box end (user's left, debris's right)
  );
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

void Player::reset()
{
  position = defaultPosition;
  location = Location::Bottom;
}
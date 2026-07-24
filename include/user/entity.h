#pragma once

#include "stdint.h"

namespace User
{
  struct Coordinates
  {
    int8_t tlx;
    int8_t tly;
    int8_t brx;
    int8_t bry;
  };

  class Entity
  {
  public:
    Entity() = delete;
    Entity(int8_t tlx, int8_t tly, int8_t brx, int8_t bry) : coordinates{tlx, tly, brx, bry} {}

    const Coordinates getPosition() const { return coordinates; }
    void setPosition(Coordinates coords) { coordinates = coords; }
    // void movePosition

    void setTopLeftX(int8_t newNumber) { coordinates.tlx = newNumber; }
    void setTopLeftY(int8_t newNumber) { coordinates.tly = newNumber; }
    void setBottomRightX(int8_t newNumber) { coordinates.brx = newNumber; }
    void setBottomRightY(int8_t newNumber) { coordinates.bry = newNumber; }

    void moveTopLeftX(int8_t offset) { coordinates.tlx += offset; }
    void moveTopLeftY(int8_t offset) { coordinates.tly += offset; }
    void moveBottomRightX(int8_t offset) { coordinates.brx += offset; }
    void moveBottomRightY(int8_t offset) { coordinates.bry += offset; }

  private:
    Coordinates coordinates;
  };
}
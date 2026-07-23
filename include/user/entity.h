#pragma once

#include "stdint.h"

namespace User
{
  struct Coordinates
  {
    uint16_t tlx;
    uint16_t tly;
    uint16_t brx;
    uint16_t bry;
  };

  class Entity
  {
  public:
    Entity() = delete;
    Entity(uint16_t tlx, uint16_t tly, uint16_t brx, uint16_t bry) : coordinates{tlx, tly, brx, bry} {}

    const Coordinates getPosition() const { return coordinates; }
    void setPosition(Coordinates coords) { coordinates = coords; }
    // void movePosition

    void setTopLeftX(uint16_t newNumber) { coordinates.tlx = newNumber; }
    void setTopLeftY(uint16_t newNumber) { coordinates.tly = newNumber; }
    void setBottomRightX(uint16_t newNumber) { coordinates.brx = newNumber; }
    void setBottomRightY(uint16_t newNumber) { coordinates.bry = newNumber; }

    void moveTopLeftX(uint16_t offset) { coordinates.tlx += offset; }
    void moveTopLeftY(uint16_t offset) { coordinates.tly += offset; }
    void moveBottomRightX(uint16_t offset) { coordinates.brx += offset; }
    void moveBottomRightY(uint16_t offset) { coordinates.bry += offset; }

  private:
    Coordinates coordinates;
  };
}
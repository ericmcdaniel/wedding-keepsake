#pragma once

#include <Arduino.h>

namespace Engine
{
  class Timer
  {
  public:
    void wait(uint32_t futureTime) { next = millis() + futureTime; }
    const bool isReady() const { return millis() >= next; };
    uint32_t nextOccurrence() const { return next; }

  private:
    uint32_t next{millis()};
  };
}
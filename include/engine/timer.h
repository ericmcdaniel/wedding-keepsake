#pragma once

#include "platform/context-manager.h"
#include <Arduino.h>

namespace Engine
{
  /*
    Provides a clean API for time management, however does not own the system
    timer directly. That's a share resource from the Context Manager.

    Works on milliseconds instead of microseconds because this is for game logic,
    microseconds is rarely needed. The frame refresh rate is only 60Hz.
  */
  class Timer
  {
  public:
    Timer(Platform::Time &t) : time{t}, next{time.getMillisecond()} {}

    void wait(uint32_t futureTime) { next = time.getMillisecond() + futureTime; }
    const bool isReady() const { return time.getMillisecond() >= next; };
    uint32_t nextOccurrence() const { return next; }

  private:
    Platform::Time &time;
    uint32_t next;
  };
}
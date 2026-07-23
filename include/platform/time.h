#pragma once
#include <Arduino.h>

namespace Platform
{
  class Time
  {
  public:
    Time() : us{micros()}, ms{us / 1000} {}

    inline uint32_t getMicrosecond() { return us; }
    inline uint32_t getMillisecond() { return ms; }

    inline void update()
    {
      us = micros();
      ms = us / 1000;
    }

  private:
    uint32_t us;
    uint32_t ms;
  };
}
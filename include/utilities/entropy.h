#pragma once

#include <stdint.h>
#include "platform/time.h"

namespace Platform
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Utilities
{
  class Entropy
  {
  public:
    Entropy(Platform::Time &t) : time{t} {}
    void begin();
    void update(uint32_t currentTime);
    uint32_t random();
    uint32_t random(uint32_t range);

    template <typename T>
    T randomEnum(T maxValue) { return static_cast<T>(random() % static_cast<uint32_t>(maxValue)); }

  private:
    Platform::Time &time;
    uint32_t state = 0xA341316C;
    bool adcBusy = false;
    uint32_t previouslyUsed = 0;

    static uint32_t mix(uint32_t value);
    void stir(uint32_t value);
    void startAdc();
    bool readAdc(uint32_t &value);
  };
}
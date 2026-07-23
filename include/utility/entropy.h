#pragma once

#include <stdint.h>
#include "platform/time.h"

namespace Platform
{
  // forward declaration because of ContextManager/OledDisplay circular dependency
  class ContextManager;
}

namespace Utility
{
  class Entropy
  {
  public:
    Entropy(Platform::Time *t) : time{t} {}
    void begin();
    void update(uint32_t currentTime);
    uint32_t get();

  private:
    Platform::Time *time;
    uint32_t state = 0xA341316C;
    bool adcBusy = false;

    static uint32_t mix(uint32_t value);
    void stir(uint32_t value);
    void startAdc();
    bool readAdc(uint16_t &value);
  };
}
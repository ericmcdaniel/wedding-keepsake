#pragma once

#include <Arduino.h>

namespace Platform
{
  class Entropy
  {
  public:
    void begin();
    void update(uint32_t currentTime);
    uint32_t get();

  private:
    uint32_t state = 0xA341316C;
    bool adcBusy = false;

    static uint32_t mix(uint32_t value);
    void stir(uint32_t value);
    void startADC();
    bool readADC(uint16_t &value);
  };
}
#include "utility/entropy.h"
#include <Arduino.h>

namespace Utility
{
  void Entropy::begin()
  {
    // PB3 floating ADC input
    PORTB.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTB.DIRCLR = PIN3_bm;
    ADC0.CTRLA = ADC_ENABLE_bm;
    ADC0.CTRLC = ADC_PRESC_DIV16_gc | ADC_REFSEL_VDDREF_gc;
    ADC0.MUXPOS = ADC_MUXPOS_AIN11_gc;

    stir(micros());
  }

  void Entropy::update(uint32_t currentTimeMicros)
  {
    stir(currentTimeMicros);

    if (!adcBusy)
    {
      startAdc();
      return;
    }

    uint16_t sample;

    if (readAdc(sample))
    {
      stir(sample);
      adcBusy = false;
    }
  }

  void Entropy::startAdc()
  {
    ADC0.COMMAND = ADC_STCONV_bm;
    adcBusy = true;
  }

  bool Entropy::readAdc(uint16_t &value)
  {
    if (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
      return false;

    ADC0.INTFLAGS = ADC_RESRDY_bm;

    value = ADC0.RES;

    return true;
  }

  void Entropy::stir(uint32_t value)
  {
    state ^= mix(value + state);
  }

  uint32_t Entropy::get()
  {
    state = mix(state + micros());
    return state;
  }

  uint32_t Entropy::mix(uint32_t value)
  {
    // Anyone reading this, there's a very interesting video about how RNG was implemented on the original
    // NES. What seems so trivial is so math intensive. https://www.youtube.com/watch?v=HSUvPVTVRCw

    // Shamelessly stolen from the MurmurHash3 algorithm, the final stage
    // https://en.wikipedia.org/wiki/MurmurHash
    value ^= value >> 16;
    value *= 0x85EBCA6B;
    value ^= value >> 13;
    value *= 0xC2B2AE35;
    value ^= value >> 16;

    return value;
  }
}
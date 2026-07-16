#include "lights/led-luminance.h"

using namespace Lights;

uint16_t LedLuminance::getLuminance()
{
  return currentLuminance;
}

void LedLuminance::adjustLuminance()
{
  // uint16_t dialReading = analogRead(SystemCore::Configuration::ledDimmerGpio);
  uint16_t dialReading = LedLuminance::MAX_ADC_READING; // read from active brightness level
  dialReading = map(dialReading, 0, LedLuminance::MAX_ADC_READING, 0, LedLuminance::MAX_LED_BRIGHTNESS);
  dialReading = constrain(dialReading, 0, LedLuminance::MAX_LED_BRIGHTNESS);

  currentLuminance = dialReading;
}

// TODO: Borrowed from LumenLab, however it was never used. Investigate.
uint8_t LedLuminance::applyGamma(uint8_t value)
{
  constexpr float gamma = 2.8f;
  float normalized = value / 255.0f;
  return static_cast<uint8_t>(powf(normalized, gamma) * 255.0f + 0.5f);
}

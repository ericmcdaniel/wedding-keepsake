#include "lights/led-matrix.h"
#include "clamp.h"

using namespace Lights;

LedMatrix::LedMatrix()
{
  reset();
}

Color *LedMatrix::getRawColors()
{
  return static_cast<Color *>(buffer.data());
}

void LedMatrix::reset()
{
  for (uint16_t i = 0; i < Platform::Configuration::numLeds; i++)
  {
    buffer[i] = Color{};
    // layer[i] = Engine::Layer::Background; //TODO: confirm, can this be removed?
  }
}

void LedMatrix::adjustLuminance()
{
  luminance.adjustLuminance();
  float brightnessScale = static_cast<float>(luminance.getLuminance()) / LedLuminance::MAX_LED_BRIGHTNESS;
  constexpr float redGain = 0.90f;
  constexpr float greenGain = 0.75f;
  constexpr float blueGain = 0.60f;

  for (uint16_t i = 0; i < Platform::Configuration::numLeds; ++i)
  {
    Color &c = buffer[i];

    float r = c.r * brightnessScale;
    float g = c.g * brightnessScale;
    float b = c.b * brightnessScale;

    r *= redGain;
    g *= greenGain;
    b *= blueGain;

    r = CustomDataStructures::clamp(r, 0.0f, 255.0f);
    g = CustomDataStructures::clamp(g, 0.0f, 255.0f);
    b = CustomDataStructures::clamp(b, 0.0f, 255.0f);

    c.r = LedLuminance::applyGamma(static_cast<uint8_t>(r));
    c.g = LedLuminance::applyGamma(static_cast<uint8_t>(g));
    c.b = LedLuminance::applyGamma(static_cast<uint8_t>(b));
  }
}

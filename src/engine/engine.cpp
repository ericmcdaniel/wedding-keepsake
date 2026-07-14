#include "engine/engine.h"
#include "platform/configuration.h"
#include "logger.h"

using namespace Engine;

GameEngine::GameEngine()
{
  initializeEngine();
}

void GameEngine::initializeEngine()
{
  contextManager.initializeSystemMemory();
  // contextManager.renderer.leds.reset(); //TODO: Remember to reset the LED matrix
  renderFrame();

  // If debugging, ensure serial connection is stable before setting up components
#if defined(VIRTUALIZATION) || defined(DEBUG)
  Serial.begin(Platform::Configuration::serialBaud);
  while (!Serial)
  {
    delay(100);
  }
  log("Serial connection established.");

  log("Printing environment variables.");
  logf("numLeds = %u", Platform::Configuration::numLeds);
  logf("serialBaud = %u", Platform::Configuration::serialBaud);
  logf("startupState = %u\n", Platform::Configuration::startupState());
#endif

  log("Startup process completed. Transitioning to the first animation.");
}

void GameEngine::renderFrame()
{
  // contextManager.renderer.leds.adjustLuminance(); //TODO: Luminance
#ifdef VIRTUALIZATION
  Serial.write(0xAA); // sync bytes
  Serial.write(0x55);
  // Serial.write(reinterpret_cast<uint8_t *>(contextManager.renderer.leds.getRawColors()), SystemCore::Configuration::numLeds() * sizeof(Lights::Color));
  // TODO: stream bits
#endif

#ifdef RELEASE
  // TODO: implement multiplex with PWM for RGB values.
#endif
}

void GameEngine::runApplication()
{
}
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
  renderFrameRow(); // TODO: clear?

  // If debugging, ensure serial connection is stable before setting up components
#ifdef DEBUG
  Serial.begin(Platform::Configuration::serialBaud);
  while (!Serial)
  {
    delay(100);
  }
#endif

  log("Serial connection established.");
  log("Printing environment variables.");
  logf("numLeds = %u", Platform::Configuration::numLeds);
  logf("serialBaud = %u", Platform::Configuration::serialBaud);
  logf("startupState = %u\n", Platform::Configuration::startupState());
  log("Startup process completed. Transitioning to the first animation.");
}

void GameEngine::renderFrameRow()
{
  // contextManager.renderer.leds.adjustLuminance(); //TODO: Luminance
  // TODO: gamma correction?

  // TODO: implement multiplex with PWM for RGB values. Psuedocode:

  disableActiveRow();
  setNextRow();
  // sendColumns(buffer[activeRow]);
  enableActiveRow();
}

void GameEngine::runApplication()
{
  while (contextManager.stateManager.isRunning())
  {
    contextManager.renderer.leds.reset();
    contextManager.renderer.leds(0, 1);
    // contextManager.controller.poll(); // TODO: poll from tactile switch

    uint32_t now = micros();
    if (now - lastFrame >= frameRefreshRate)
    {
      lastFrame += frameRefreshRate;

      switch (contextManager.stateManager.current())
      {
      case SystemState::Initialize:
        break;
        // case SystemState::Animation_1:
        // contextManager.application->nextEvent();
        // break;
      case SystemState::Error:
        // TODO: (maybe) Animate an error state?
        break;
      default:
        // ideally shouldn't encounter this
        contextManager.stateManager.setNext(SystemState::Error);
        break;
      }
    }

    if (now - lastRender >= rowRefreshRate)
    {
      lastRender += rowRefreshRate;
      renderFrameRow();
    }
  }
}

inline void GameEngine::disableActiveRow()
{
  // TODO: Finish
  // psuedocode:
  // diitalWrite(activeRow, LOW)
}

inline void GameEngine::enableActiveRow()
{
  // TODO: Finish
  // someting like digitalWrite(activeRow, HIGH)
}

inline void GameEngine::setNextRow()
{
  activeRow++;
  if (activeRow >= 4)
  {
    activeRow = 0;
  }
}
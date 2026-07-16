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
  // renderFrameRow(); // TODO: clear?

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

  pinMode(PIN_PA1, OUTPUT);
  pinMode(PIN_PA2, OUTPUT);
  pinMode(PIN_PA3, OUTPUT);
  pinMode(PIN_PA4, OUTPUT);
  pinMode(PIN_PA5, OUTPUT);
  pinMode(PIN_PA6, OUTPUT);
  pinMode(PIN_PA7, OUTPUT);

  digitalWrite(PIN_PA4, HIGH);
  digitalWrite(PIN_PA5, HIGH);
  digitalWrite(PIN_PA6, HIGH);
  digitalWrite(PIN_PA7, HIGH);
}

void GameEngine::renderFrameRow()
{
  // contextManager.renderer.leds.adjustLuminance(); //TODO: Luminance? Gamma correction?

  disableActiveRow();
  setNextRow();

  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;

  const uint8_t bit = (1 << bamBitPlane);

  for (uint8_t col = 0; col < Platform::Configuration::numColumns; col++)
  {
    const Lights::Color pixel = Lights::ColorCode::ThemeGreen;

    if (pixel.r & bit)
    {
      red |= (1 << col);
    }

    if (pixel.g & bit)
    {
      green |= (1 << col);
    }

    if (pixel.b & bit)
    {
      blue |= (1 << col);
    }

    shiftOutByte(~red);
    shiftOutByte(~green);
    shiftOutByte(~blue);

    // latch high then low
    PORTA.OUTSET = PIN3_bm;
    PORTA.OUTCLR = PIN3_bm;

    setNextRow();
    enableActiveRow();

    bamCounter++;

    if (bamCounter >= bamDurations[bamBitPlane])
    {
      bamCounter = 0;
      bamBitPlane++;

      if (bamBitPlane >= 8)
      {
        bamBitPlane = 0;
      }
    }
  }
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
  PORTA.OUTSET = rowMask;
}

inline void GameEngine::enableActiveRow()
{
  PORTA.OUTCLR = (PIN4_bm << activeRow);
}

inline void GameEngine::setNextRow()
{
  activeRow++;
  if (activeRow >= Platform::Configuration::numRows)
  {
    activeRow = 0;
  }
}

void GameEngine::shiftOutByte(uint8_t value)
{
  for (int8_t i = 7; i >= 0; i--)
  {
    if (value & (1 << i))
    {
      // PA1 high
      PORTA.OUTSET = PIN1_bm;
    }
    else
    {
      // PA1 low
      PORTA.OUTCLR = PIN1_bm;
    }

    PORTA.OUTSET = PIN2_bm; // same format as above, PA2 high
    PORTA.OUTCLR = PIN2_bm; // PA2 low
  }
}
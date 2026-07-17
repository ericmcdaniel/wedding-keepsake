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

  // pin setup
  PORTA.DIRSET = PIN1_bm | PIN2_bm | PIN3_bm |
                 PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

  // pin set to high
  PORTA.OUTSET = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
}

void GameEngine::runApplication()
{
  while (contextManager.stateManager.isRunning())
  {
    contextManager.renderer.leds.reset();
    contextManager.renderer.leds(0, 1);
    // contextManager.controller.poll(); // TODO: poll from tactile switch

    uint32_t now = micros();

    if (now - lastColorActivation >= 1000000)
    {
      // colorIdx = (colorIdx + 1) & 5;
      colorIdx = (colorIdx + 1) % 16;
      lastColorActivation += 1000000;
    }

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

void GameEngine::renderFrameRow()
{
  // contextManager.renderer.leds.adjustLuminance(); //TODO: Luminance? Gamma correction?

  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint8_t currentColor = colorIdx;

  disableActiveRow();
  setNextRow();

  const uint8_t bit = (1 << bamBitPlane);

  for (uint8_t col = 0; col < Platform::Configuration::numColumns; col++)
  {
    // const Lights::Color pixel = Lights::ColorCode::ThemeGreen;
    const Lights::Color pixel = colorArray[currentColor];

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
  }

  shiftOutByte(~red);
  shiftOutByte(~green);
  shiftOutByte(~blue);

  // latch high then low
  PORTA.OUTSET = PIN3_bm;
  PORTA.OUTCLR = PIN3_bm;

  enableActiveRow();
  // if (activeRow == 0)
  // {
  shiftBamBit();
  // }
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
  activeRow = (activeRow + 1) & (Platform::Configuration::numRows - 1);
}

void GameEngine::shiftOutByte(uint8_t value)
{
  for (int8_t i = 7; i >= 0; i--)
  {
    if (value & (1 << i))
    {
      PORTA.OUTSET = PIN1_bm; // PA1 high to 74HC595 data pin
    }
    else
    {
      PORTA.OUTCLR = PIN1_bm; // PA1 low
    }

    PORTA.OUTSET = PIN2_bm; // same format as above, PA2 high
    PORTA.OUTCLR = PIN2_bm; // PA2 low
  }
}

inline void GameEngine::shiftBamBit()
{
  // This is an optimization of the original implementation, which
  // used a counter increasing from 0-255, and verified the row
  // that was activated based on bit position.
  if (++bamCounter >= (1u << bamBitPlane))
  {
    bamCounter = 0;
    bamBitPlane = (bamBitPlane + 1) & 0x7;
  }
}
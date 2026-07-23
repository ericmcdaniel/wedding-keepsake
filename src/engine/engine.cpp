#include "engine/engine.h"
#include "platform/configuration.h"
#include "lights/color-correction.h"
#include "utility/logger.h"

using namespace Engine;

KeychainEngine::KeychainEngine()
{
  initializeEngine();
}

void KeychainEngine::initializeEngine()
{
  contextManager.initializeSystemMemory();

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

  // immediately set PA4-7 as HIGH, the row MOSFET is active low.
  PORTA.OUTSET = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

  // setup pins PA1-7 as output
  PORTA.DIRSET = PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;

  contextManager.entropy.begin();
  contextManager.changeApplication(Platform::Configuration::startupState());
}

void KeychainEngine::runApplication()
{
  while (contextManager.stateManager.isRunning())
  {
    contextManager.time.update();
    contextManager.entropy.update(contextManager.time.getMicrosecond());
    contextManager.button.update(contextManager.time.getMillisecond());

    if (contextManager.button.wasHeld())
    {
      // TODO: do better than this...
      SystemState nextState = contextManager.stateManager.current() == SystemState::Animation ? SystemState::Game : SystemState::Animation;
      contextManager.changeApplication(nextState);
      continue;
    }

    if (contextManager.time.getMicrosecond() - lastFullFrameRender >= frameRefreshRate)
    {
      lastFullFrameRender += frameRefreshRate;
      contextManager.application->nextEvent();
    }

    if (contextManager.time.getMicrosecond() - lastMatrixRowRender >= rowRefreshRate)
    {
      lastMatrixRowRender += rowRefreshRate;
      renderFrameRow();
    }
  }
}

void KeychainEngine::renderFrameRow()
{
  disableActiveRow();
  pwmAdjustAndShiftToLeds();
  toggleLatch();
  enableActiveRow();
  selectNextMatrixRow();
  shiftBamBit();
}

inline void KeychainEngine::disableActiveRow()
{
  PORTA.OUTSET = rowMask;
}

inline void KeychainEngine::enableActiveRow()
{
  PORTA.OUTCLR = (PIN4_bm << activeRow);
}

inline void KeychainEngine::selectNextMatrixRow()
{
  activeRow = (activeRow + 1) & (Platform::Configuration::numRows - 1);
}

void KeychainEngine::pwmAdjustAndShiftToLeds()
{
  const uint8_t bamSequenceBit = (1 << bamSequence[bamBitPlane]);

  uint8_t adjustedRed = 0;
  uint8_t adjustedGreen = 0;
  uint8_t adjustedBlue = 0;

  for (uint8_t col = 0; col < Platform::Configuration::numColumns; col++)
  {
    Lights::Color pixel = contextManager.renderer.getPixel(activeRow, col);

    pixel = Lights::ColorCorrection::apply(pixel);

    const uint8_t r = Lights::LedBrightness::apply(reduceTo6Bit(pixel.r));
    const uint8_t g = Lights::LedBrightness::apply(reduceTo6Bit(pixel.g));
    const uint8_t b = Lights::LedBrightness::apply(reduceTo6Bit(pixel.b));

    if (r & bamSequenceBit)
    {
      adjustedRed |= (1 << col);
    }

    if (g & bamSequenceBit)
    {
      adjustedGreen |= (1 << col);
    }

    if (b & bamSequenceBit)
    {
      adjustedBlue |= (1 << col);
    }
  }

  shiftOutByte(~adjustedRed);
  shiftOutByte(~adjustedGreen);
  shiftOutByte(~adjustedBlue);
}

inline void KeychainEngine::toggleLatch()
{
  // latch high then low
  PORTA.OUTSET = PIN3_bm;
  PORTA.OUTCLR = PIN3_bm;
}

void KeychainEngine::shiftOutByte(uint8_t value)
{
  for (int8_t i = 7; i >= 0; i--)
  {
    if (value & (1 << i))
    {
      PORTA.OUTSET = PIN1_bm; // PA1 high to 74HC595 data pin
    }
    else
    {
      PORTA.OUTCLR = PIN1_bm; // PA1 (data pin) low
    }

    PORTA.OUTSET = PIN2_bm; // same format as above, PA2 high
    PORTA.OUTCLR = PIN2_bm; // PA2 low
  }
}

inline void KeychainEngine::shiftBamBit()
{
  // This is an optimization of the original implementation, which
  // used a counter increasing from 0-255, and verified the row
  // that was activated based on bit position.
  if (++bamCounter >= (1u << bamSequence[bamBitPlane]))
  {
    bamCounter = 0;
    bamBitPlane++;

    if (bamBitPlane >= 6)
    {
      bamBitPlane = 0;
    }
  }
}

uint8_t KeychainEngine::reduceTo6Bit(uint8_t value)
{
  return value >> 2;
}

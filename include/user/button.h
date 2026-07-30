#pragma once

#include <Arduino.h>

namespace User
{
  class Button
  {
  public:
    Button();
    void update(uint32_t currentTime);
    bool wasSinglePress();
    bool wasDoublePress();
    bool wasHeld();
    void reset();
    static inline void interruptHandler() { interruptCount++; }

  private:
    enum class State
    {
      Idle,
      PressedDebouncing,
      PressedStable,
      ReleaseDebouncing,
      WaitingForSecondPress,
      WaitingForRelease
    };

    inline static uint8_t consumeInterruptCount();
    void handlePress(uint32_t currentTime);
    void handleRelease(uint32_t currentTime);

    static volatile uint8_t interruptCount;
    State state = State::Idle;
    bool singlePress = false;
    bool doublePress = false;
    bool secondPressPending = false;
    bool completingDoublePress = false;
    bool held = false;
    uint32_t stateTimestamp = 0;
    static constexpr uint32_t debounceTime = 10;
    static constexpr uint32_t doublePressWindow = 70;
    static constexpr uint32_t holdTime = 1000;
    bool holdTriggered = false;
  };
}

#pragma once

#include <Arduino.h>

namespace User
{
  class Button
  {
  public:
    void update(uint32_t currentTime);
    bool wasSinglePress() const { return singlePress; };
    bool wasDoublePress() const { return doublePress; };
    bool wasHeld() const { return held; };
    static void interruptHandler() { interruptTriggered = true; }

  private:
    enum class State
    {
      Idle,
      Debouncing,
      Pressed,
      WaitingForSecondPress,
      WaitingForRelease
    };

    void clearEvents();
    void handlePress();
    void handleRelease();

    static volatile bool interruptTriggered;
    State state = State::Idle;
    bool singlePress = false;
    bool doublePress = false;
    bool held = false;
    uint32_t stateTimestamp = 0;
    static constexpr uint16_t debounceTime = 30;
    static constexpr uint16_t doublePressWindow = 300;
    static constexpr uint16_t holdTime = 1000;
    bool holdTriggered = false;
  };
}

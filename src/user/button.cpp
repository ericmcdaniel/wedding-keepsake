#include "user/button.h"
#include "platform/configuration.h"

using namespace User;

volatile uint8_t Button::interruptCount = 0;

//
// Hardware interrupt.
// Must be global. AVR interrupt vectors cannot point directly to class member functions.
//
ISR(PORTB_PORT_vect)
{
  if (PORTB.INTFLAGS & Platform::Configuration::pinButton)
  {
    // Clears/sets interrupt flag
    PORTB.INTFLAGS = Platform::Configuration::pinButton;
    Button::interruptHandler();
  }
}

Button::Button()
{
  // Set PB0 (the SMD button) is input with internal pull-up resistor, and as a falling-edge interrupt
  PORTB.DIRCLR = Platform::Configuration::pinButton;
  PORTB.PIN0CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
}

inline uint8_t Button::consumeInterruptCount()
{
  noInterrupts();
  uint8_t count = Button::interruptCount;
  Button::interruptCount = 0;
  interrupts();

  return count;
}

void Button::update(uint32_t currentTimeMillis)
{
  const uint8_t count = consumeInterruptCount();
  const bool pressed = !(PORTB.IN & Platform::Configuration::pinButton);

  if (count || pressed)
  {
    switch (state)
    {
    case State::Idle:
      state = State::PressedDebouncing;
      stateTimestamp = currentTimeMillis;
      break;
    case State::WaitingForSecondPress:
      if (currentTimeMillis - stateTimestamp <= doublePressWindow)
      {
        completingDoublePress = true;
        state = State::PressedDebouncing;
        stateTimestamp = currentTimeMillis;
      }
      else
      {
        singlePress = true;
        completingDoublePress = false;
        state = State::PressedDebouncing;
        stateTimestamp = currentTimeMillis;
      }
      break;
    default:
      break;
    }
  }

  if (state == State::PressedDebouncing)
  {
    if (currentTimeMillis - stateTimestamp >= debounceTime)
    {
      if (pressed)
      {
        handlePress(currentTimeMillis);
      }
      else
      {
        // The press was shorter than the debounce window. Treat the interrupt
        // as a real quick tap instead of dropping the press completely.
        handlePress(stateTimestamp);
        handleRelease(currentTimeMillis);
      }
    }
  }

  // button is currently held down, need to determine if being held or double pressed
  if (state == State::PressedStable)
  {
    if (!holdTriggered && currentTimeMillis - stateTimestamp >= holdTime)
    {
      held = true;
      holdTriggered = true;
      state = State::WaitingForRelease; // stop generating events until release.
    }
    else if (!pressed) // normal release
    {
      state = State::ReleaseDebouncing;
      stateTimestamp = currentTimeMillis;
    }
  }

  if (state == State::ReleaseDebouncing)
  {
    if (pressed)
    {
      state = State::PressedStable;
    }
    else if (currentTimeMillis - stateTimestamp >= debounceTime)
    {
      handleRelease(currentTimeMillis);
    }
  }

  // after hold, wait until release.
  if (state == State::WaitingForRelease)
  {
    if (!pressed)
    {
      state = State::Idle;
    }
  }

  // no second press, interpret as as a single press.
  if (state == State::WaitingForSecondPress)
  {
    if (currentTimeMillis - stateTimestamp > doublePressWindow)
    {
      singlePress = true;
      completingDoublePress = false;
      state = State::Idle;
    }
  }
}

void Button::handlePress(uint32_t currentTimeMillis)
{
  if (completingDoublePress)
  {
    doublePress = true;
    secondPressPending = true;
    completingDoublePress = false;
  }

  state = State::PressedStable;
  stateTimestamp = currentTimeMillis;
  holdTriggered = false;
}

void Button::handleRelease(uint32_t currentTimeMillis)
{
  // Ignore release after hold
  if (holdTriggered)
  {
    state = State::Idle;
    return;
  }

  if (secondPressPending)
  {
    secondPressPending = false;
    state = State::Idle;
    return;
  }

  // Begin double-click detection.
  state = State::WaitingForSecondPress;
  stateTimestamp = currentTimeMillis;
}

bool Button::wasSinglePress()
{
  if (singlePress)
  {
    singlePress = false;
    return true;
  }

  return false;
}

bool Button::wasDoublePress()
{
  if (doublePress)
  {
    doublePress = false;
    singlePress = false;
    return true;
  }

  return false;
}

bool Button::wasHeld()
{
  if (held)
  {
    held = false;
    return true;
  }

  return false;
}

void Button::reset()
{
  singlePress = false;
  doublePress = false;
  secondPressPending = false;
  completingDoublePress = false;
  held = false;
  state = State::Idle;
  stateTimestamp = 0;
  holdTriggered = false;
  consumeInterruptCount();
}

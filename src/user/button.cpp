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

void Button::update(uint32_t currentTimeMillis)
{
  uint8_t count = Button::interruptCount;
  if (count)
  {
    Button::interruptCount = 0;

    switch (state)
    {
    case State::Idle:
      state = State::Debouncing;
      stateTimestamp = currentTimeMillis;
      break;
    case State::WaitingForSecondPress:
      if (currentTimeMillis - stateTimestamp <= doublePressWindow)
      {
        completingDoublePress = true;
        state = State::Debouncing;
        stateTimestamp = currentTimeMillis;
      }
      else
      {
        completingDoublePress = false;
        state = State::Debouncing;
        stateTimestamp = currentTimeMillis;
      }
      break;
    default:
      break;
    }
  }

  if (state == State::Debouncing)
  {
    if (currentTimeMillis - stateTimestamp >= debounceTime)
    {
      bool pressed = !(PORTB.IN & Platform::Configuration::pinButton);

      if (pressed)
      {
        handlePress(currentTimeMillis);
      }
      else
      {
        state = State::Idle;
      }
    }
  }

  // button is currently held down, need to determine if being held or double pressed
  if (state == State::Pressed)
  {
    if (!holdTriggered && currentTimeMillis - stateTimestamp >= holdTime)
    {
      held = true;
      holdTriggered = true;
      state = State::WaitingForRelease; // stop generating events until release.
    }
    else if (PORTB.IN & Platform::Configuration::pinButton) // Normal release.
    {
      handleRelease(currentTimeMillis);
    }
  }

  // after hold, wait until release.
  if (state == State::WaitingForRelease)
  {
    // read if button is pressed
    if (PORTB.IN & Platform::Configuration::pinButton)
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

  state = State::Pressed;
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

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
  if (PORTB.INTFLAGS & PIN0_bm)
  {
    // Clears/sets interrupt flag
    PORTB.INTFLAGS = PIN0_bm;
    Button::interruptHandler();
  }
}

void Button::update(uint32_t currentTime)
{
  uint8_t count = Button::interruptCount;
  if (count)
  {
    Button::interruptCount = 0;

    switch (state)
    {
    case State::Idle:
      state = State::Debouncing;
      stateTimestamp = currentTime;
      break;
    case State::WaitingForSecondPress:
      if (currentTime - stateTimestamp <= doublePressWindow)
      {
        completingDoublePress = true;
        state = State::Debouncing;
        stateTimestamp = currentTime;
      }
      else
      {
        completingDoublePress = false;
        state = State::Debouncing;
        stateTimestamp = currentTime;
      }
      break;
    default:
      break;
    }
  }

  if (state == State::Debouncing)
  {
    if (currentTime - stateTimestamp >= debounceTime)
    {
      bool pressed = !(PORTB.IN & Platform::Configuration::buttonPin);

      if (pressed)
      {
        handlePress(currentTime);
      }
      else
      {
        state = State::Idle;
      }
    }
  }

  // button is currently held down
  if (state == State::Pressed)
  {
    if (!holdTriggered && currentTime - stateTimestamp >= holdTime)
    {
      held = true;
      holdTriggered = true;
      state = State::WaitingForRelease; // stop generating events until release.
    }
    else if (PORTB.IN & Platform::Configuration::buttonPin) // Normal release.
    {
      handleRelease(currentTime);
    }
  }

  // after hold, wait until release.
  if (state == State::WaitingForRelease)
  {
    if (PORTB.IN & Platform::Configuration::buttonPin)
    {
      state = State::Idle;
    }
  }

  // no second press, interpret as as a single press.
  if (state == State::WaitingForSecondPress)
  {
    if (currentTime - stateTimestamp > doublePressWindow)
    {
      singlePress = true;
      completingDoublePress = false;
      state = State::Idle;
    }
  }
}

void Button::handlePress(uint32_t currentTime)
{
  if (completingDoublePress)
  {
    doublePress = true;
    secondPressPending = true;
    completingDoublePress = false;
  }

  state = State::Pressed;
  stateTimestamp = currentTime;
  holdTriggered = false;
}

void Button::handleRelease(uint32_t currentTime)
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
  stateTimestamp = currentTime;
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

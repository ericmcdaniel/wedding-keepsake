#include "user/button.h"
#include "platform/configuration.h"

using namespace User;

volatile bool Button::interruptTriggered = false;

//
// Hardware interrupt.
//
// Must be global. AVR interrupt vectors cannot point
// directly to class member functions.
//
ISR(PORTB_PORT_vect)
{
  // Clears/sets interrupt flag
  PORTB.INTFLAGS = PIN2_bm;
  Button::interruptHandler();
}

void Button::update(uint32_t currentTime)
{
  clearEvents();

  if (interruptTriggered)
  {
    interruptTriggered = false;
    switch (state)
    {
    case State::Idle:
      state = State::Debouncing;
      stateTimestamp = currentTime;
      break;
    case State::WaitingForSecondPress:
      if (currentTime - stateTimestamp <= doublePressWindow)
      {
        doublePress = true;
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
        handlePress();
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
      handleRelease();
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
      state = State::Idle;
    }
  }
}

void Button::handlePress()
{
  state = State::Pressed;
  stateTimestamp = millis();
  holdTriggered = false;
}

void Button::handleRelease()
{
  // Ignore release after hold.
  if (holdTriggered)
  {
    state = State::Idle;
    return;
  }

  // Begin double-click detection.
  state = State::WaitingForSecondPress;
  stateTimestamp = millis();
}

void Button::clearEvents()
{
  singlePress = false;
  doublePress = false;
  held = false;
}

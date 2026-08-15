#ifdef CLEAR
#include <Arduino.h>
#include <EEPROM.h>
void setup()
{

  for (uint16_t i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.update(i, 0);
  }
}
void loop() {}
#else

#include <Arduino.h>
#include "engine/engine.h"

void setup()
{
  Engine::KeychainEngine engine;
  engine.runApplication();
}

/**
 * loop() functions just as a catch block does in modern try/catch exception handling.
 * There is no game logic here.
 */
void loop()
{
  Serial.println("Keychain has encountered an unrecoverable error state.");
  delay(1000);
}
#endif
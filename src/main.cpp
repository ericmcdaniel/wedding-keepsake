#include <Arduino.h>
// #include "engine/engine.h"

void setup()
{
  // Engine::GameEngine engine;
  // engine.runApplication();
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

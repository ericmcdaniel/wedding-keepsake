#include "platform/configuration.h"
#include <EEPROM.h>

using namespace Platform;

void Configuration::load()
{
  _startupSystemState = EEPROM.get(4, _startupSystemState);
}
#include "platform/configuration.h"

using namespace Platform;

void Configuration::load()
{
  _startupState = Engine::SystemState::Initialize;

  // TODO: read from eeprom here
}
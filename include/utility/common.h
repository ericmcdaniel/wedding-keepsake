#pragma once

#include <stdint.h>

template <typename T, uint16_t N>
constexpr uint16_t arraySize(const T (&)[N]) { return N; }

#pragma once

#ifdef NATIVE
#include <chrono>

unsigned long millis();

#else

#include <Arduino.h>

#endif

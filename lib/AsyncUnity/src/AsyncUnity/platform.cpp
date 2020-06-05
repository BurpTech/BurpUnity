#include "./platform.hpp"

#ifdef NATIVE

unsigned long millis() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

#else
#include <Arduino.h>
#endif

#include <cstdio>
#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <BddUnity.hpp>

#include "module1.hpp"
#include "module2.hpp"

Runnables<2> runnables = {
  &Module1::tests,
  &Module2::tests,
};

Runner<2> runner(runnables);
Memory memory;
bool running = true;
int status;


void setup() {
  UNITY_BEGIN();
  BddUnity::Usage::printParams(memory);
  runner.setup(memory);
}

void loop() {
  if (running) {
    runner.loop();
    if (runner.isFinished()) {
      BddUnity::Usage::printUsage(memory, runner);
      status = UNITY_END();
      running = false;
    }
  }
}

int main() {
  setup();
  while (running) {
    loop();
  }
  return status;
}


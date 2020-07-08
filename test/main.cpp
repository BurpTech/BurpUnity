#include <cstdio>
#ifndef BURP_NATIVE
#include <Arduino.h>
#endif

#define BURP_UNITY_MAX_MODULE 1
#define BURP_UNITY_MAX_DESCRIBE 2
#define BURP_UNITY_MAX_POP 4
#define BURP_UNITY_MAX_TEST 4
#define BURP_UNITY_MAX_IT 3
#define BURP_UNITY_MAX_ASYNC_IT 2
#define BURP_UNITY_MAX_CALLBACK 3
#define BURP_UNITY_MAX_ASYNC_CALLBACK 3
#define BURP_UNITY_MAX_STACKED_CALLBACK 4
#define BURP_UNITY_MAX_STACKED_ASYNC_CALLBACK 4
#define BURP_UNITY_MAX_SETUP 1
#define BURP_UNITY_MAX_DEPTH 4
#define BURP_UNITY_MAX_BEFORE_EACH 2
#define BURP_UNITY_MAX_ASYNC_BEFORE_EACH 2
#define BURP_UNITY_MAX_AFTER_EACH 2
#define BURP_UNITY_MAX_ASYNC_AFTER_EACH 2
#define BURP_UNITY_MAX_LOOP 4

#include <unity.h>
#include <BurpUnity.hpp>

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
  BurpUnity::Usage::printParams(memory);
  runner.setup(memory);
}

void loop() {
  if (running) {
    runner.loop();
    if (runner.isFinished()) {
      BurpUnity::Usage::printUsage(memory, runner);
      BurpUnity::Usage::printUsageDefines(memory, runner, 1);
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


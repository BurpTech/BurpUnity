#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <BddUnity.hpp>
#include <MyLib.hpp>

int status;
MyLib myLib;

Module module("MyLib", [](Describe & describe) {

  describe.it("should fail", []() {
    TEST_ASSERT_TRUE(false);
  });

  describe.async("callMeNextLoop", [](Async & async, f_done & done) {
    myLib.callMeNextLoop(100, [&](int value) {
      async.it("should pass", [&]() {
        TEST_ASSERT_EQUAL(100, value);
      });
      async.it("should fail", [&]() {
        TEST_ASSERT_EQUAL(10, value);
      });
      // signal that we are done, this
      // should not be done in a function
      // that asserts as the assert may
      // exit that function before it gets
      // there and thus cause a timeout
      // failure
      done();
    });
  });

  describe.it("should pass", []() {
    TEST_ASSERT_TRUE(true);
  });

});

void setup()
{
  UNITY_BEGIN();
  module.start();
}

void loop()
{
  myLib.loop();
  module.loop();
  if (!module.isRunning()) {
    status = UNITY_END();
  }
}

int main()
{
  setup();

  while (module.isRunning())
  {
    loop();
  }

  return status;
}


#ifndef NATIVE
#include <Arduino.h>
#endif

#include <AsyncUnity.hpp>
#include <AsyncUnity/Globals.hpp>

#include <MyLib.hpp>

MyLib myLib;

Root root(ROOT_NAME("MyLib"), [](Describe & describe) {

  describe.it(NAME("should fail"), []() {
    TEST_ASSERT_TRUE(false);
  });

  describe.it(NAME("should pass"), []() {
    TEST_ASSERT_TRUE(true);
  });

  describe.it(NAME("should call me with value"), [](f_done & done, f_test & test) {
    myLib.callMeNextLoop(100, [&](int value) {
      test(NAME("should pass"), [&]() {
        TEST_ASSERT_EQUAL(100, value);
      });
      test(NAME("should fail"), [&]() {
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

});

void setup()
{
  myLib.setup();
  root.start();
}

void loop()
{
  myLib.loop();
  root.loop();
}

int main()
{
  setup();
  while (root.isRunning())
  {
    loop();
  }

  return root.status;
}


#ifndef NATIVE
#include <Arduino.h>
#endif

#include <AsyncUnity.hpp>
#include <AsyncUnity/Globals.hpp>

#include <MyLib.hpp>

MyLib myLib;

Root root(__FILE__, "MyLib", __LINE__, [](Describe & describe) {

  describe.it("should fail", __LINE__, []() {
    TEST_ASSERT_TRUE(false);
  });

  describe.it("should pass", __LINE__, []() {
    TEST_ASSERT_TRUE(true);
  });

  describe.it("should call me with value", __LINE__, [](f_done & done, f_test & test) {
    myLib.callMeNextLoop(100, [&](int value) {
      test("sub test 1", __LINE__, [&]() {
        TEST_ASSERT_EQUAL(100, value);
      });
      // signal that we are done, this
      // should not be done in a function
      // that asserts as the assert will
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
  root.setup();
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

  // Print the actual memory usage for tuning
  size_t size = 256;
  char buffer[size];
  puts("");
  puts("AsyncUnity: Build flags:\n");
  AsyncUnity::Globals::snprintFlags(buffer, size);
  puts(buffer);
  puts("AsyncUnity: Actual memory usage:\n");
  AsyncUnity::Globals::snprintMemory(buffer, size);
  puts(buffer);

  return root.status;
}


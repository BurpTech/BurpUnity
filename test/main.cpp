#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <BddUnity.hpp>
#include <MyLib.hpp>

int status;
bool running = true;

MyLib myLib1;
MyLib myLib2;

Memory memory;

Module module1(memory, "MyLib1", [](Describe & describe) {

  describe.it("should fail", []() {
    TEST_ASSERT_TRUE(false);
  });

  describe.async("callMeNextLoop", [](Async & async, f_done & done) {
    myLib1.callMeNextLoop(100, [&](int value) {
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

Module module2(memory, "MyLib2", [](Describe & describe) {

  describe.it("should fail", []() {
    TEST_ASSERT_TRUE(false);
  });

  describe.async("callMeNextLoop", [](Async & async, f_done & done) {
    myLib2.callMeNextLoop(100, [&](int value) {
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

  // print the memory configuration
  char buffer[512];
  memory.snprintParams(buffer, 512);
  puts(buffer);
}

void loop()
{
  myLib1.loop();
  myLib2.loop();

  if (module1.isRunning() || module2.isRunning()) {
    module1.loop();
    module2.loop();
  } else {

    // print the actual memory usage
    char buffer[512];
    memory.snprintUsage(buffer, 512);
    puts(buffer);
    module1.snprintMaxDepth(buffer, 512);
    puts(buffer);
    module2.snprintMaxDepth(buffer, 512);
    puts(buffer);

    status = UNITY_END();
    running = false;
  }
}

int main()
{
  setup();

  while (running)
  {
    loop();
  }

  return status;
}

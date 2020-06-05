#ifndef NATIVE
#include <Arduino.h>
#endif

#include <AsyncUnity.hpp>
#include <AsyncUnity/Globals.hpp>

#include <MyLib.hpp>

Root root(__FILE__, "my module", __LINE__, [](Describe & describe) {
  describe.describe("my thing", __LINE__, [&](Describe & describe) {
    describe.it("should fail", __LINE__, [&]() {
      TEST_ASSERT_TRUE(false);
    });
    describe.it("should pass", __LINE__, [&]() {
      TEST_ASSERT_TRUE(true);
    });
    describe.it("should fail asynchronously", __LINE__, [&](f_test test) {
      test("sub test", __LINE__, [&](f_done done) {
        TEST_ASSERT_TRUE(false);
        done(nullptr);
      });
    });
  });
});

void setup()
{
  root.setup();
}

void loop()
{
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
  char buffer[100];
  AsyncUnity::Globals::snprintMemory(buffer, 100);
  puts(buffer);

  return root.status;
}


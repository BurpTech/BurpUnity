#include <stdio.h>
#include <functional>
#include <unity.h>
#include "module1.hpp"
#include "module2.hpp"

namespace Module1 {

  class Callback {
    public:

      using f_cb = std::function<void()>;

      Callback() :
        _cb(nullptr)
      {}

      void setup() {
        printf("Callback::setup\n");
      }

      void loop() {
        // printf("Callback::loop\n");
        if (_cb) {
          _cb();
          _cb = nullptr;
        }
      }

      void callback(f_cb cb) {
        _cb = cb;
      }

    private:

      f_cb _cb;

  };

  // As we need to access this asynchronously it
  // has to be global so that it doesn't go out of
  // scope
  Callback callback;

  Module module("module 1", [](Describe & describe) {

    describe.setup([&]() {
      printf("setup\n");
      callback.setup();
    });

    describe.loop([&]() {
      // printf("loop\n");
      callback.loop();
    });

    describe.before([&]() {
      printf("before\n");
    });

    describe.after([&]() {
      printf("after\n");
    });

    describe.beforeEach([&](f_done & done) {
      callback.callback([&]() {
        printf("beforeEach\n");
        done();
      });
    });

    describe.afterEach([&](f_done & done) {
      callback.callback([&]() {
        printf("afterEach\n");
        done();
      });
    });

    describe.it("should pass", [&]() {
      TEST_ASSERT_TRUE(true);
    });

    describe.it("should also pass", [&]() {
      TEST_ASSERT_TRUE(true);
    });

    describe.describe("another test", [&](Describe & describe) {

      describe.setup([&]() {
        printf("another setup\n");
      });

      describe.loop([&]() {
        // printf("another loop\n");
      });

      describe.include(Module2::module);

      describe.before([&](f_done & done) {
        callback.callback([&]() {
          printf("another before\n");
          done();
        });
      });

      describe.after([&](f_done & done) {
        callback.callback([&]() {
          printf("another after\n");
          done();
        });
      });

      describe.beforeEach([&]() {
        printf("another beforeEach\n");
      });

      describe.afterEach([&]() {
        printf("another afterEach\n");
      });

      describe.it("should pass", [&]() {
        TEST_ASSERT_TRUE(true);
      });

      describe.async("async", [&](Async & async, f_done & done) {

        callback.callback([&]() {

          async.it("should pass", [&]() {
            TEST_ASSERT_TRUE(true);
          });

          async.it("should also pass", [&]() {
            TEST_ASSERT_TRUE(true);
          });

          done();

        });

      });

    });

  });

}

#include <stdio.h>
#include <functional>
#include <unity.h>
#include <Callback.hpp>
#include "module2.hpp"

namespace Module2 {

  // As we need to access this asynchronously it
  // has to be global so that it doesn't go out of
  // scope
  Callback callback;

  Module tests("module 2", [](Describe & describe) {

    describe.setup([&]() {
      printf("setup\n");
    });

    describe.loop([&]() {
      callback.loop();
    });

    describe.before([&]() {
      printf("before\n");
    });

    describe.after([&]() {
      printf("after\n");
    });

    describe.beforeEach([&](f_done & done) {
      callback.once([&]() {
        printf("beforeEach\n");
        done();
      });
    });

    describe.afterEach([&](f_done & done) {
      callback.once([&]() {
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

      describe.before([&](f_done & done) {
        callback.once([&]() {
          printf("another before\n");
          done();
        });
      });

      describe.after([&](f_done & done) {
        callback.once([&]() {
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

        callback.once([&]() {

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

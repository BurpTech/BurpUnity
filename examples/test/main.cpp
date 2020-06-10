#ifndef NATIVE
#include <Arduino.h>
#endif

#include <functional>
#include <unity.h>
#include <BddUnity.hpp>

int status;

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

Callback callback;
Memory memory;
Module module(memory, "test", [](Describe & describe) {

  describe.setup([]() {
    printf("setup\n");
    callback.setup();
  });

  describe.loop([]() {
    // printf("loop\n");
    callback.loop();
  });

  describe.before([]() {
    printf("before\n");
  });

  describe.after([]() {
    printf("after\n");
  });

  describe.beforeEach([](f_done & done) {
    callback.callback([&]() {
      printf("beforeEach\n");
      done();
    });
  });

  describe.afterEach([](f_done & done) {
    callback.callback([&]() {
      printf("afterEach\n");
      done();
    });
  });

  describe.it("should pass", []() {
    TEST_ASSERT_TRUE(true);
  });

  describe.it("should also pass", []() {
    TEST_ASSERT_TRUE(true);
  });

  describe.describe("another test", [](Describe & describe) {

    describe.setup([]() {
      printf("another setup\n");
    });

    describe.loop([]() {
      // printf("another loop\n");
    });

    describe.before([](f_done & done) {
      callback.callback([&]() {
        printf("another before\n");
        done();
      });
    });

    describe.after([](f_done & done) {
      callback.callback([&]() {
        printf("another after\n");
        done();
      });
    });

    describe.beforeEach([]() {
      printf("another beforeEach\n");
    });

    describe.afterEach([]() {
      printf("another afterEach\n");
    });

    describe.it("should pass", []() {
      TEST_ASSERT_TRUE(true);
    });

    describe.async("async", [](Async & async, f_done & done) {

      callback.callback([&]() {

        async.it("should pass", []() {
          TEST_ASSERT_TRUE(true);
        });

        async.it("should also pass", []() {
          TEST_ASSERT_TRUE(true);
        });

        done();

      });

    });

  });

});

void setup() {
  UNITY_BEGIN();
}

void loop() {
  if (module.isRunning()) {
    module.loop();
  } else {
    status = UNITY_END();
  }
}

int main() {
  setup();
  while (module.isRunning()) {
    loop();
  }
  return status;
}

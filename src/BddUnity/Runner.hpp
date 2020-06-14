#pragma once

#include <array>
#include <algorithm>
#include <cstddef>
#include <functional>
#include "Depth/Interface.hpp"
#include "Runnable.hpp"

namespace BddUnity {

  template <size_t size>
  using Runnables = std::array<Runnable *, size>;

  template <size_t size>
  class Runner : public Runnable {

    public:

      Runner(Runnables<size> runnables) :
        _runnables(runnables),
        _state(Runnable::State::IDLE),
        _setup(nullptr)
      {}

      void setup(Memory::Interface & memory) override {
        _setup = [&](Runnable * runnable) {
          runnable->setup(memory);
        };
        _state = Runnable::State::RUNNING;
      }

      void loop() override {
        if (isRunning()) {
          _state = Runnable::State::FINISHED;
          for (auto runnable : _runnables) {
            if (runnable) {
              switch (runnable->getState()) {
                case Runnable::State::FINISHED:
                  // check for errors
                  if (runnable->hasError) {
                    setError(runnable->error);
                    // stop on error
                    return;
                  }
                  break;
                case Runnable::State::IDLE:
                  _state = Runnable::State::RUNNING;
                  _setup(runnable);
                  //we only run one module at a time
                  return;
                case Runnable::State::RUNNING:
                  _state = Runnable::State::RUNNING;
                  runnable->loop();
                  //we only run one module at a time
                  return;
              }
            }
          }
        }
      }

      Runnable::State getState() override {
        return _state;
      }

#define MAX_VALUE(FIRST, SECOND, NAME) std::max(FIRST.NAME, SECOND.NAME)

      const Depth::Usage getUsage() const override {
        using f_max = std::function<Depth::Usage(const Depth::Usage & first, const Depth::Usage & second)>;
        f_max max = [](const Depth::Usage & first, const Depth::Usage & second) {
          Depth::Usage ret = {
            MAX_VALUE(first, second, maxDepth),
            MAX_VALUE(first, second, maxBeforeEach),
            MAX_VALUE(first, second, maxAsyncBeforeEach),
            MAX_VALUE(first, second, maxAfterEach),
            MAX_VALUE(first, second, maxAsyncAfterEach),
            MAX_VALUE(first, second, maxLoop)
          };
          return ret;
        };
        Depth::Usage usage = {0,0,0,0,0,0};
        for (auto runnable : _runnables) {
          usage = max(usage, runnable->getUsage());
        }
        return usage;
      }

    private:

      using f_setup = std::function<void(Runnable * runnable)>;

      Runnables<size> _runnables;
      Runnable::State _state;
      f_setup _setup;

  };

}

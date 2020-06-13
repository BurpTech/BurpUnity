#pragma once

#include <array>
#include <functional>
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
                break;
              case Runnable::State::RUNNING:
                _state = Runnable::State::RUNNING;
                runnable->loop();
                //we only run one module at a time
                return;
            }
          }
        }
      }

      Runnable::State getState() override {
        return _state;
      }

    private:

      using f_setup = std::function<void(Runnable * runnable)>;

      Runnables<size> _runnables;
      Runnable::State _state;
      f_setup _setup;

  };

}

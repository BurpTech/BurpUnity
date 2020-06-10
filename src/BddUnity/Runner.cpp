#include "Runner.hpp"
#include "Runnable.hpp"

namespace BddUnity {

  Runner::Runner(Runnable ** runnables) :
    _runnables(runnables),
    _state(Runnable::State::IDLE),
    _setup(nullptr)
  {}

  void Runner::setup(Memory::Interface & memory) {
    _setup = [&](Runnable * runnable) {
      runnable->setup(memory);
    };
    _state = Runnable::State::RUNNING;
  }

  void Runner::loop() {
    if (isRunning()) {
      Runnable ** runnable = _runnables;
      _state = Runnable::State::FINISHED;
      while (*runnable) {
        switch ((*runnable)->getState()) {
          case Runnable::State::FINISHED:
            // check for errors
            if ((*runnable)->hasError) {
              setError((*runnable)->error);
              // stop on error
              return;
            }
            break;
          case Runnable::State::IDLE:
            _state = Runnable::State::RUNNING;
            _setup(*runnable);
            break;
          case Runnable::State::RUNNING:
            _state = Runnable::State::RUNNING;
            (*runnable)->loop();
            //we only run one module at a time
            return;
        }
        runnable++;
      }
    }
  }

  Runnable::State Runner::getState() {
    return _state;
  }

}

#include "Runnable.hpp"

namespace BurpUnity {

  bool Runnable::isIdle() {
    return getState() == State::IDLE;
  }

  bool Runnable::isRunning() {
    return getState() == State::RUNNING;
  }

  bool Runnable::isFinished() {
    return getState() == State::FINISHED;
  }

}

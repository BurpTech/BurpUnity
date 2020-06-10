#include "Runnable.hpp"

namespace BddUnity {

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

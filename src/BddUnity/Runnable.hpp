#pragma once

#include "HasError.hpp"
#include "Memory/Interface.hpp"

namespace BddUnity {

  class Runnable : public HasError {
    
    public:

      enum class State {
        IDLE,
        RUNNING,
        FINISHED
      };

      virtual void setup(Memory::Interface & memory) = 0;
      virtual void loop() = 0;
      virtual State getState() = 0;
      bool isIdle();
      bool isRunning();
      bool isFinished();

  };

}

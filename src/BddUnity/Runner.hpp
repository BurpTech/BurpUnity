#pragma once

#include <functional>
#include "Runnable.hpp"

namespace BddUnity {

  class Runner : public Runnable {

    public:

      Runner(Runnable ** runnables);
      void setup(Memory::Interface & memory) override;
      void loop() override;
      Runnable::State getState() override;

    private:

      using f_setup = std::function<void(Runnable * runnable)>;

      Runnable ** _runnables;
      Runnable::State _state;
      f_setup _setup;

  };

}

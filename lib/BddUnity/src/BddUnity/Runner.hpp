#pragma once

#include "Module.hpp"

namespace BddUnity {

  class Runner {

    public:

      Runner(Module ** modules, bool parallel = false);
      void loop();
      bool isRunning();

    private:

      Module ** _modules;
      bool _parallel;
      bool _running;

  };

}

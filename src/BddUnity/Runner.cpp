#include "Runner.hpp"

namespace BddUnity {

  Runner::Runner(Module ** modules, bool parallel) :
    _modules(modules),
    _parallel(parallel),
    _running(true)
  {}

  void Runner::loop() {
    Module ** module = _modules;
    _running = false;
    while (*module) {
      if ((*module)->isRunning()) {
        _running = true;
        (*module)->loop();
        // only loop the next module
        // if running in parallel
        if (!_parallel) return;
      }
      module++;
    }
  }

  bool Runner::isRunning() {
    return _running;
  }

}

#include "Setup.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace Describe {

      Setup::Setup(const int line, const f_setup cb) :
        line(line),
        cb(cb)
      {}

      Setup::Setup(Memory::Pool::Interface<Setup, Setup> * pool, const Setup & setup) :
        Memory::Pool::HasPool<Setup, Setup>(pool),
        line(setup.line),
        cb(setup.cb)
      {}

      const Error * Setup::free() {
        return Memory::Pool::HasPool<Setup, Setup>::free(this);
      }

      const Error * Setup::_free() {
        return nullptr;
      }

    }
  }
}

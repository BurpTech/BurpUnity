#include <unity.h>
#include "Instance.hpp"
#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace StackedCallback {

      Instance::Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
        Memory::Pool::HasPool<Interface, Params>(pool),
        _params(params)
      {}

      void Instance::_run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        _params.cb();
        done(nullptr);
        return;
      }

      const Error * Instance::free() {
        return Memory::Pool::HasPool<Interface, Params>::free(this);
      }

      const Error * Instance::_free() {
        return nullptr;
      }

    }
  }
}

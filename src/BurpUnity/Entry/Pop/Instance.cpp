#include "Instance.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace Pop {

      Instance::Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
        Memory::Pool::HasPool<Interface, Params>(pool)
      {}

      void Instance::_run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        done(depth.pop());
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

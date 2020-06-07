#include "Instance.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Pop {

      Instance::Instance(Factory::Interface<Interface, Params> & factory, const Params & params) :
        Factory::HasFactory<Interface, Params>(factory)
      {}

      void Instance::_run(Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        done(depth.pop());
        return;
      }

      const Error * Instance::free() {
        return Factory::HasFactory<Interface, Params>::free();
      }

      const Error * Instance::_free() {
        return nullptr;
      }

    }
  }
}

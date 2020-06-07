#include <unity.h>
#include "../../Globals.hpp"
#include "Instance.hpp"
#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace It {

      Instance::Instance(Factory::Interface<Interface, Params> & factory, const Params & params) :
        Factory::HasFactory<Interface, Params>(factory),
        _params(params)
      {}

      void Instance::_run(Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        const char * label = depth.getLabel(_params.should);
        // we do this as the UnityTestFunction type
        // does not allow us to bind any context so
        // we effectively pass it through a global
        Globals::testCallback = _params.it;
        UnityDefaultTestRun([]() {
            Globals::testCallback();
        }, label, _params.line);
        done(nullptr);
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

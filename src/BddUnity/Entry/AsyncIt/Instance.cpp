#include <unity.h>
#include "../../Globals.hpp"
#include "Instance.hpp"

namespace BddUnity {
  namespace Entry {
    namespace AsyncIt {

      Instance::Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
        Memory::Pool::HasPool<Interface, Params>(pool),
        _params(params)
      {}

      const Error * Instance::free() {
        return Memory::Pool::HasPool<Interface, Params>::free();
      }

      void Instance::_run(List & list, Depth::Interface & depth, Timeout & timeout, const Interface::f_done & done) {
        timeout.label = _params.thing;
        timeout.line = _params.line;
        timeout.timeout = depth.getTimeout(_params.timeout);
        // use [=] in _done lambda to make a copy of the
        // synchronous done function as it will go out of scope
        // by the next loop, the function it points to will still
        // be there though so that's ok (it is a std::bind on Root::_done)
        _done = [=]() {
          // don't let tests use done to report an error
          done(nullptr);
        };
        new(&_async) Async(&depth, _params.thing);
        _params.it(_async, _done);
      }

      const Error * Instance::_free() {
        return nullptr;
      }

    }
  }
}

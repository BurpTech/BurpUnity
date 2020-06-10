#include "Instance.hpp"
#include <cstdio>

namespace BddUnity {
  namespace Entry {
    namespace Test {

      Instance::Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
        Memory::Pool::HasPool<Interface, Params>(pool),
        _params(params)
      {
        // append the entry to the internal list
        // to keep track of whether we need to free it
        _list.append(_params.entry);
      }

      const Error * Instance::free() {
        return Memory::Pool::HasPool<Interface, Params>::free(this);
      }

      void Instance::_run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;

        // add the beforeEach callbacks
        List beforeEach;
        const Error * e = depth.beforeEach(beforeEach, _params.stackedCallbackPool, _params.stackedAsyncCallbackPool);
        if (e) {
          // failed to allocate beforeEach callbacks
          setError(*e, _params.label, "prepend beforeEach", _params.line);
          done(&error);
          return;
        }
        _list.prepend(beforeEach);

        // add the afterEach callback
        List afterEach;
        e = depth.afterEach(afterEach, _params.stackedCallbackPool, _params.stackedAsyncCallbackPool);
        if (e) {
          // failed to allocate before callbacks
          setError(*e, _params.label, "append afterEach", _params.line);
          done(&error);
          return;
        }
        _list.append(afterEach);

        // now transfer the entries
        // to the master list
        _list.transfer(list);

        // and we're done
        done(nullptr);
        return;
      }

      const Error * Instance::_free() {
        return _list.freeAll();
      }

    }
  }
}

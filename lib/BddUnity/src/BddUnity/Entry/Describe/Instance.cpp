#include "Instance.hpp"
#include "../AsyncIt/Params.hpp"
#include "../It/Params.hpp"
#include "../Pop/Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Describe {

      Instance::Instance(Factory::Interface<Interface, Params> & factory, const Params & params) :
        Factory::HasFactory<Interface, Params>(factory),
        _params(params)
      {}

      const Error * Instance::free() {
        return Factory::HasFactory<Interface, Params>::free();
      }

      void Instance::describe(const char * thing, const Params::f_describe describe, const long timeout) {
        Instance::describe(thing, 0, describe, timeout);
      }

      void Instance::describe(const char * thing, const int line, const Params::f_describe describe, const long timeout) {
        Params params = {
          _params.memory,
          thing,
          line,
          describe,
          timeout
        };
        Interface * entry = _factory.create(params);
        if (entry) {
          _append(entry);
        } else {
          setError(_factory.error, thing, line);
        }
      }

      void Instance::async(const char * thing, const AsyncIt::Params::f_async it, const long timeout) {
        Instance::async(thing, 0, it, timeout);
      }

      void Instance::async(const char * thing, const int line, const AsyncIt::Params::f_async it, const long timeout) {
        AsyncIt::Params params = {
          thing,
          line,
          it,
          timeout
        };
        Factory::Interface<Interface, AsyncIt::Params> & factory = _params.memory.getAsyncItFactory();
        Interface * entry = factory.create(params);
        if (entry) {
          _append(entry);
        } else {
          setError(factory.error, thing, line);
        }
      }

      void Instance::it(const char * should, const It::Params::f_testCallback it) {
        Instance::it(should, 0, it);
      }

      void Instance::it(const char * should, const int line, const It::Params::f_testCallback it) {
        It::Params params = {
          should,
          line,
          it
        };
        Factory::Interface<Interface, It::Params> & factory = _params.memory.getItFactory();
        Interface * entry = factory.create(params);
        if (entry) {
          _append(entry);
        } else {
          setError(factory.error, should, line);
        }
      }

      void Instance::_run(Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        const Error * e = depth.push(_params.thing, _params.timeout);
        if (e) {
          // failed to increase the depth
          setError(*e, _params.thing, _params.line);
          done(&error);
          return;
        }

        // collect the new entries
        _params.describe(*this);

        // check for error (eg: from MemPool allocation)
        if (hasError) {
          done(&error);
          return;
        }

        // append a pop to the entries
        Pop::Params params = {};
        Factory::Interface<Interface, Pop::Params> & factory = _params.memory.getPopFactory();
        Interface * entry = factory.create(params);
        if (!entry) {
          // I don't think this can happen
          // as the depth would be exceeded first
          setError(factory.error, _params.thing, _params.line);
          done(&error);
          return;
        }
        _append(entry);

        // now insert the entries as next
        // and clear the local reference
        _entriesTail->next = next;
        next = _entries;
        _entries = nullptr;

        // and we're done
        done(nullptr);
        return;
      }

      void Instance::_append(Interface * entry) {
        if (_entries) {
          _entriesTail->next = entry;
        } else {
          _entries = entry;
        }
        _entriesTail = entry;
      }

      const Error * Instance::_free() {
        const Error * ret = nullptr;
        const Error * e = nullptr;
        while (_entries) {
          e = _entries->free();
          if (e) ret = e;
          _entries = _entries->next;
        }
        return ret;
      }

    }
  }
}

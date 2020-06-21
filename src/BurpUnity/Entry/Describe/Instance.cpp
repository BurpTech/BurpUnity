#include <functional>
#include "Instance.hpp"
#include "../AsyncIt/Params.hpp"
#include "../It/Params.hpp"
#include "../Pop/Params.hpp"
#include "../../Depth/Frame.hpp"

#define IMPLEMENT_CALLBACK(NAME, ERROR_CODE)\
  void Instance::NAME(const int line, const Callback::Params::f_callback cb) {\
    if (_##NAME) {\
      setError(Error::Code::ERROR_CODE, _params.thing, line);\
      return;\
    }\
    Callback::Params params = {\
      _params.thing,\
      line,\
      cb\
    };\
    _##NAME = _params.callbackPool.create(params);\
    if (!_##NAME) {\
      setError(_params.callbackPool.error, _params.thing, #NAME, line);\
    }\
  }\
  void Instance::NAME(const Callback::Params::f_callback cb) {\
    NAME(0, cb);\
  }\
  void Instance::NAME(const int line, const AsyncCallback::Params::f_async cb, const long timeout) {\
    if (_##NAME) {\
      setError(Error::Code::ERROR_CODE, _params.thing, line);\
      return;\
    }\
    AsyncCallback::Params params = {\
      _params.thing,\
      line,\
      cb,\
      timeout\
    };\
    _##NAME = _params.asyncCallbackPool.create(params);\
    if (!_##NAME) {\
      setError(_params.asyncCallbackPool.error, _params.thing, #NAME, line);\
    }\
  }\
  void Instance::NAME(const AsyncCallback::Params::f_async cb, const long timeout) {\
    NAME(0, cb, timeout);\
  }

#define IMPLEMENT_STACKED_CALLBACK(NAME, DEPTH_FUNCTION)\
  void Instance::NAME(const int line, const StackedCallback::Params::f_callback cb) {\
    StackedCallback::Params params = {\
      _params.thing,\
      line,\
      cb\
    };\
    const Error * e = _params.depth.DEPTH_FUNCTION(params);\
    if (e) setError(*e, "before", line);\
  }\
  void Instance::NAME(const StackedCallback::Params::f_callback cb) {\
    NAME(0, cb);\
  }\
  void Instance::NAME(const int line, const StackedAsyncCallback::Params::f_async cb, const long timeout) {\
    StackedAsyncCallback::Params params = {\
      _params.thing,\
      line,\
      cb,\
      timeout\
    };\
    const Error * e = _params.depth.DEPTH_FUNCTION(params);\
    if (e) setError(*e, "before", line);\
  }\
  void Instance::NAME(const StackedAsyncCallback::Params::f_async cb, const long timeout) {\
    NAME(0, cb, timeout);\
  }

namespace BurpUnity {
  namespace Entry {
    namespace Describe {

      Instance::Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
        Memory::Pool::HasPool<Interface, Params>(pool),
        _params(params),
        _setup(nullptr),
        _before(nullptr),
        _after(nullptr)
      {}

      const Error * Instance::free() {
        return Memory::Pool::HasPool<Interface, Params>::free(this);
      }

      IMPLEMENT_CALLBACK(before, BEFORE_SET)
      IMPLEMENT_CALLBACK(after, AFTER_SET)
      IMPLEMENT_STACKED_CALLBACK(beforeEach, setBeforeEach)
      IMPLEMENT_STACKED_CALLBACK(afterEach, setAfterEach)

      void Instance::include(Module & module) {
        using namespace std::placeholders;
        module._include(std::bind(
          static_cast<void(Instance::*)(
            const char * thing,
            const int line,
            const Params::f_describe describe,
            const long timeout
          )>(&Instance::describe),
          this, _1, _2, _3, _4
        ));
      }

      void Instance::describe(const char * thing, const Params::f_describe describe, const long timeout) {
        Instance::describe(thing, 0, describe, timeout);
      }

      void Instance::describe(const char * thing, const int line, const Params::f_describe describe, const long timeout) {
        Params params = {
          _params.depth,
          _params.popPool,
          _params.testPool,
          _params.itPool,
          _params.asyncItPool,
          _params.callbackPool,
          _params.asyncCallbackPool,
          _params.stackedCallbackPool,
          _params.stackedAsyncCallbackPool,
          _params.setupPool,
          thing,
          line,
          describe,
          timeout
        };
        Interface * entry = _pool->create(params);
        if (entry) {
          _list.append(entry);
        } else {
          setError(_pool->error, thing, line);
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
        Interface * entry = _params.asyncItPool.create(params);
        if (entry) {
          // wrap in a test so that it can be expanded
          // with beforeEach and afterEach entries
          _addTest(entry, thing, line);
        } else {
          setError(_params.asyncItPool.error, thing, line);
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
        Interface * entry = _params.itPool.create(params);
        if (entry) {
          // wrap in a test so that it can be expanded
          // with beforeEach and afterEach entries
          _addTest(entry, should, line);
        } else {
          setError(_params.itPool.error, should, line);
        }
      }

      void Instance::setup(const Setup::f_setup cb) {
        setup(0, cb);
      }

      void Instance::setup(const int line, const Setup::f_setup cb) {
        if (_setup) {
          setError(Error::Code::HAS_SETUP, _params.thing, line);
          return;
        }
        Setup setup(line, cb);
        _setup = _params.setupPool.create(setup);
        if (!_setup) {
          setError(_params.setupPool.error, _params.thing, "setup", line);
        }
      }

      void Instance::loop(const Loop::f_loop cb) {
        loop(0, cb);
      }

      void Instance::loop(const int line, const Loop::f_loop cb) {
        Loop loop = { line, cb };
        const Error * e = _params.depth.setLoop(loop);
        if (e) setError(*e, "loop", line);
      }

      void Instance::_run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) {
        timeout.timeout = Timeout::NO_TIMEOUT;
        Depth::Frame frame(_params.thing, _params.timeout);
        const Error * e = depth.push(frame);
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

        // Call the setup callback immediately
        if (_setup) {
          _setup->cb();
          e = _setup->free();
          _setup = nullptr;
          if (e) {
            setError(*e, "setup", _params.line);
            done(&error);
            return;
          }
        }

        // add the before callback
        if (_before) {
          _list.prepend(_before);
          _before = nullptr;
        }

        // add the after callback
        if (_after) {
          _list.append(_after);
          _after = nullptr;
        }

        // append a pop to the entries
        Pop::Params params = {};
        Interface * entry = _params.popPool.create(params);
        if (!entry) {
          // I don't think this can happen
          // as the depth would be exceeded first
          setError(_params.popPool.error, "append pop", _params.line);
          done(&error);
          return;
        }
        _list.append(entry);

        // now transfer the entries
        // to the master list
        _list.transfer(list);

        // and we're done
        done(nullptr);
        return;
      }

      void Instance::_addTest(Interface * entry, const char * label, const int line) {
        Test::Params params = {
          label,
          line,
          _params.stackedCallbackPool,
          _params.stackedAsyncCallbackPool,
          entry
        };
        Interface * test = _params.testPool.create(params);
        if (test) {
          _list.append(test);
        } else {
          setError(_params.testPool.error, label, line);
        }
      }

      const Error * Instance::_free() {
        const Error * ret = nullptr;
        if (_setup) {
          const Error * e = _setup->free();
          if (e) ret = e;
        }
        if (_before) {
          const Error * e = _before->free();
          if (e) ret = e;
        }
        if (_after) {
          const Error * e = _after->free();
          if (e) ret = e;
        }
        const Error * e = _list.freeAll();
        if (e) ret = e;
        return ret;
      }

    }
  }
}

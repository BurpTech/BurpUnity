#include <unity.h>
#include "../Globals.hpp"
#include "AsyncIt.hpp"

namespace AsyncUnity {
  namespace Entry {

    AsyncIt * AsyncIt::create(const char * should, const int line, const f_async it, const long timeout) {
      void * address = Globals::asyncItMemPool.alloc();
      if (address) {
        return new(address) AsyncIt(should, line, it, timeout);
      }
      setStaticError(Globals::asyncItMemPool.error, should, line);
      return nullptr;
    }

    const Error * AsyncIt::free() {
      return Globals::asyncItMemPool.free(this);
    }

    void AsyncIt::run(const Entry::f_done & done) {
      Globals::timeout.label = _should;
      Globals::timeout.line = _line;
      Globals::timeout.timeout = Globals::depth.getTimeout(_timeout);
      // use [=] in asyncDone lambda to make a copy of the
      // synchronous done function as it will go out of scope
      // by the next loop, the function it points to will still
      // be there though so that's ok (it is a std::bind on Root::_done)
      Globals::asyncDone = [=]() {
        // don't let tests use done to report an error
        done(nullptr);
      };
      Globals::asyncTest = [&](const char * field, const int line, f_testCallback cb) {
        const char * label = Globals::depth.getLabel(_should, field);
        // we do this as the UnityTestFunction type
        // does not allow us to bind any context so
        // we effectively pass it through a global
        Globals::asyncTestCallback = cb;
        UnityDefaultTestRun([]() {
            Globals::asyncTestCallback();
        }, label, line);
      };
      _it(Globals::asyncDone, Globals::asyncTest);
    }

    AsyncIt::AsyncIt(const char * should, const int line, const f_async it, const unsigned long timeout) :
      _should(should),
      _line(line),
      _it(it),
      _timeout(timeout) {}

  }
}

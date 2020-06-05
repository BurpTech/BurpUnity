#include <unity.h>
#include "./AsyncIt.hpp"
#include "../Globals.hpp"

namespace AsyncUnity {
  namespace Entry {

    const Error * AsyncIt::error = nullptr;

    AsyncIt * AsyncIt::create(const char * should, const int line, const f_async it, const long timeout) {
      void * address = Globals::asyncItMemPool.alloc();
      if (address) {
        return new(address) AsyncIt(should, line, it, timeout);
      }
      error = Globals::asyncItMemPool.error;
      return nullptr;
    }

    const Error * AsyncIt::free() {
      return Globals::asyncItMemPool.free(this);
    }

    void AsyncIt::run(Entry::f_done done) {
      Globals::timeout.label = _should;
      Globals::timeout.line = _line;
      Globals::timeout.timeout = Globals::depth.getTimeout(_timeout);
      _it([=]() {
        // don't let tests use done to report an error
        done(nullptr);
      }, [&](const char * field, const int line, f_testCallback cb) {
        const char * label = Globals::depth.getLabel(_should, field);
        // we do this as the UnityTestFunction type
        // does not allow us to bind any context so
        // we effectively pass it through a global
        Globals::asyncTestCallback = cb;
        UnityDefaultTestRun([]() {
            Globals::asyncTestCallback();
        }, label, line);
      });
    }

    AsyncIt::AsyncIt(const char * should, const int line, const f_async it, const unsigned long timeout) :
      _should(should),
      _line(line),
      _it(it),
      _timeout(timeout) {}

  }
}

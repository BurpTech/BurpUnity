#include <unity.h>
#include "../Globals.hpp"
#include "AsyncIt.hpp"

namespace AsyncUnity {
  namespace Entry {

    AsyncIt::Async::Async() :
      _thing(nullptr)
    {}

    AsyncIt::Async::Async(const char * thing) :
      _thing(thing)
    {}

    void AsyncIt::Async::it(const char * should, const f_testCallback it) {
      Async::it(should, 0, it);
    }

    void AsyncIt::Async::it(const char * should, const int line, const f_testCallback it) {
      const char * label = Globals::depth.getLabel(_thing, should);
      // we do this as the UnityTestFunction type
      // does not allow us to bind any context so
      // we effectively pass it through a global
      Globals::asyncTestCallback = it;
      UnityDefaultTestRun([]() {
          Globals::asyncTestCallback();
      }, label, line);
    }

    AsyncIt * AsyncIt::create(const char * thing, const int line, const f_async it, const long timeout) {
      void * address = Globals::asyncItMemPool.alloc();
      if (address) {
        return new(address) AsyncIt(thing, line, it, timeout);
      }
      setStaticError(Globals::asyncItMemPool.error, thing, line);
      return nullptr;
    }

    const Error * AsyncIt::free() {
      return Globals::asyncItMemPool.free(this);
    }

    void AsyncIt::run(const Entry::f_done & done) {
      Globals::timeout.label = _thing;
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
      new(&Globals::async) Async(_thing);
      _it(Globals::async, Globals::asyncDone);
    }

    AsyncIt::AsyncIt(const char * thing, const int line, const f_async it, const unsigned long timeout) :
      _thing(thing),
      _line(line),
      _it(it),
      _timeout(timeout) {}

  }
}

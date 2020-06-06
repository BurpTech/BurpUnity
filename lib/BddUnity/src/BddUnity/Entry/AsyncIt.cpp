#include <unity.h>
#include "../Globals.hpp"
#include "AsyncIt.hpp"

namespace BddUnity {
  namespace Entry {

    AsyncIt::Async::Async(Context::Interface & context, const char * thing) :
      Context::HasContext(context),
      _thing(thing)
    {}

    void AsyncIt::Async::it(const char * should, const f_testCallback it) {
      Async::it(should, 0, it);
    }

    void AsyncIt::Async::it(const char * should, const int line, const f_testCallback it) {
      const char * label = _context.getDepth().getLabel(_thing, should);
      // we do this as the UnityTestFunction type
      // does not allow us to bind any context so
      // we effectively pass it through a global
      Globals::asyncTestCallback = it;
      UnityDefaultTestRun([]() {
          Globals::asyncTestCallback();
      }, label, line);
    }

    AsyncIt * AsyncIt::create(Context::Interface & context, const char * thing, const int line, const f_async it, const long timeout) {
      MemPool::Interface & memPool = context.getAsyncItMemPool();
      void * address = memPool.alloc();
      if (address) {
        return new(address) AsyncIt(context, thing, line, it, timeout);
      }
      setStaticError(memPool.error, thing, line);
      return nullptr;
    }

    const Error * AsyncIt::free() {
      return _context.getAsyncItMemPool().free(this);
    }

    void AsyncIt::run(Timeout & timeout, const Interface::f_done & done) {
      timeout.label = _thing;
      timeout.line = _line;
      timeout.timeout = _context.getDepth().getTimeout(_timeout);
      // use [=] in asyncDone lambda to make a copy of the
      // synchronous done function as it will go out of scope
      // by the next loop, the function it points to will still
      // be there though so that's ok (it is a std::bind on Root::_done)
      Globals::asyncDone = [=]() {
        // don't let tests use done to report an error
        done(nullptr);
      };
      new(Globals::async) Async(_context, _thing);
      _it(*Globals::async, Globals::asyncDone);
    }

    AsyncIt::AsyncIt(Context::Interface & context, const char * thing, const int line, const f_async it, const unsigned long timeout) :
      Interface(context),
      _thing(thing),
      _line(line),
      _it(it),
      _timeout(timeout) {}

  }
}

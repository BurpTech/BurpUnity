#include "../Globals.hpp"
#include "It.hpp"

namespace BddUnity {
  namespace Entry {

    It * It::create(Context::Interface & context, const char * should, const int line, const f_testCallback it) {
      MemPool::Interface & memPool = context.getItMemPool();
      void * address = memPool.alloc();
      if (address) {
        return new(address) It(context, should, line, it);
      }
      setStaticError(memPool.error, should, line);
      return nullptr;
    }

    const Error * It::free() {
      return _context.getItMemPool().free(this);
    }

    void It::run(Timeout & timeout, const f_done & done) {
      timeout.timeout = Timeout::NO_TIMEOUT;
      const char * label = _context.getDepth().getLabel(_should);
      // we do this as the UnityTestFunction type
      // does not allow us to bind any context so
      // we effectively pass it through a global
      Globals::testCallback = _it;
      UnityDefaultTestRun([]() {
          Globals::testCallback();
      }, label, _line);
      done(nullptr);
      return;
    }

    It::It(Context::Interface & context, const char * should, const int line, const f_testCallback it) :
      Interface(context),
      _should(should),
      _line(line),
      _it(it) {}

  }
}

#include "./It.hpp"
#include "../Globals.hpp"

namespace AsyncUnity {
  namespace Entry {

    const Error * It::error = nullptr;

    It * It::create(const char * should, const int line, const f_testCallback it) {
      void * address = Globals::itMemPool.alloc();
      if (address) {
        return new(address) It(should, line, it);
      }
      error = Globals::itMemPool.error;
      return nullptr;
    }

    const Error * It::free() {
      return Globals::itMemPool.free(this);
    }

    void It::run(f_done done) {
      Globals::timeout.timeout = Timeout::NO_TIMEOUT;
      const char * label = Globals::depth.getLabel(_should);
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

    It::It(const char * should, const int line, const f_testCallback it) :
      _should(should),
      _line(line),
      _it(it) {}

  }
}

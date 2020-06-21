#include <unity.h>
#include "../../Globals.hpp"
#include "Async.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace AsyncIt {

      Async::Async() :
        _depth(nullptr),
        _thing(nullptr)
      {}

      Async::Async(Depth::Interface * depth, const char * thing) :
        _depth(depth),
        _thing(thing)
      {}

      void Async::it(const char * should, const f_testCallback it) {
        Async::it(should, 0, it);
      }

      void Async::it(const char * should, const int line, const f_testCallback it) {
        const char * label = _depth->getLabel(_thing, should);
        // we do this as the UnityTestFunction type
        // does not allow us to bind any context so
        // we effectively pass it through a global
        Globals::asyncTestCallback = it;
        UnityDefaultTestRun([]() {
            Globals::asyncTestCallback();
        }, label, line);
      }

    }
  }
}

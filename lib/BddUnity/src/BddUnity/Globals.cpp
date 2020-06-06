#include <memory>
#include "Globals.hpp"

namespace BddUnity {
  namespace Globals {

    int errorLine;
    const char * errorMessage;

    Entry::It::f_testCallback testCallback;
    Entry::AsyncIt::Async::f_testCallback asyncTestCallback;
    Entry::AsyncIt::f_done asyncDone;

    std::allocator<Entry::AsyncIt::Async> allocator;
    Entry::AsyncIt::Async * async = allocator.allocate(1);

  }
}

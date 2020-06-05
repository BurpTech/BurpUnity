#include "TestParams.hpp"

namespace BddUnity {
  namespace Globals {

    int testLine = 0;
    const char * testMessage = nullptr;
    Timeout timeout;
    Entry::It::f_testCallback testCallback;
    Entry::AsyncIt::Async::f_testCallback asyncTestCallback;
    Entry::AsyncIt::f_done asyncDone;
    Entry::AsyncIt::Async async;

  }
}

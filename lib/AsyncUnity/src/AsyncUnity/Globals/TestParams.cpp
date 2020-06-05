#include "./TestParams.hpp"

namespace AsyncUnity {
  namespace Globals {

    int testLine = 0;
    const char * testMessage = nullptr;
    Timeout timeout;
    Entry::It::f_testCallback testCallback;
    Entry::AsyncIt::f_testCallback asyncTestCallback;
    Entry::AsyncIt::f_done asyncDone;
    Entry::AsyncIt::f_test asyncTest;

  }
}

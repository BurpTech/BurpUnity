#include "./TestParams.hpp"

namespace AsyncUnity {
  namespace Globals {

    int testLine = 0;
    const char * testMessage = nullptr;
    Timeout timeout;
    Entry::Entry::f_done done;
    Entry::It::f_testCallback testCallback;
    Entry::AsyncIt::f_testCallback asyncTestCallback;

  }
}
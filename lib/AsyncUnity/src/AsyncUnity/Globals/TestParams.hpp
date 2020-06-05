#pragma once

#include "../Timeout.hpp"
#include "../Entry/It.hpp"
#include "../Entry/AsyncIt.hpp"

namespace AsyncUnity {
  namespace Globals {

    extern int testLine;
    extern const char * testMessage;
    extern Timeout timeout;
    extern Entry::It::f_testCallback testCallback;
    extern Entry::AsyncIt::Async::f_testCallback asyncTestCallback;
    extern Entry::AsyncIt::f_done asyncDone;
    extern Entry::AsyncIt::Async async;

  }
}

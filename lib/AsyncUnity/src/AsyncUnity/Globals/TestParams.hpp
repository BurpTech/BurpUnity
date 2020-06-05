#pragma once

#include "../Timeout.hpp"
#include "../Entry/It.hpp"
#include "../Entry/AsyncIt.hpp"

namespace AsyncUnity {
  namespace Globals {

    extern int testLine;
    extern const char * testMessage;
    extern Timeout timeout;
    extern Entry::Entry::f_done done;
    extern Entry::It::f_testCallback testCallback;
    extern Entry::AsyncIt::f_testCallback asyncTestCallback;


  }
}

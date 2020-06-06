#pragma once

#include "Entry/It.hpp"
#include "Entry/AsyncIt.hpp"

namespace BddUnity {
  namespace Globals {

    extern int errorLine;
    extern const char * errorMessage;
    extern Entry::It::f_testCallback testCallback;
    extern Entry::AsyncIt::Async::f_testCallback asyncTestCallback;
    extern Entry::AsyncIt::f_done asyncDone;
    extern Entry::AsyncIt::Async * async;

  }
}

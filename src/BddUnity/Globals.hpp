#pragma once

#include "Entry/It/Params.hpp"
#include "Entry/AsyncIt/Params.hpp"
#include "Entry/AsyncIt/Async.hpp"

namespace BddUnity {
  namespace Globals {

    extern int errorLine;
    extern const char * errorMessage;
    extern Entry::It::Params::f_testCallback testCallback;
    extern Entry::AsyncIt::Async::f_testCallback asyncTestCallback;

  }
}

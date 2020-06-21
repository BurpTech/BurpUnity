#pragma once

#include "Entry/It/Params.hpp"
#include "Entry/AsyncIt/Params.hpp"
#include "Entry/AsyncIt/Async.hpp"

namespace BurpUnity {
  namespace Globals {

    // Globals are only used for synchronous callbacks where
    // the state cannot be referenced (eg. in Unity test callbacks)
    extern int errorLine;
    extern const char * errorMessage;
    extern Entry::It::Params::f_testCallback testCallback;
    extern Entry::AsyncIt::Async::f_testCallback asyncTestCallback;

  }
}

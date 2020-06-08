#include <memory>
#include "Globals.hpp"

namespace BddUnity {
  namespace Globals {

    int errorLine;
    const char * errorMessage;

    Entry::It::Params::f_testCallback testCallback;
    Entry::AsyncIt::Async::f_testCallback asyncTestCallback;

  }
}

#pragma once

#include <functional>
#include "Async.hpp"

namespace BddUnity {
  namespace Entry {
    namespace AsyncIt {

      struct Params {

        using f_done = std::function<void()>;
        using f_async = std::function<void(Async & async, f_done & done)>;

        const char * thing;
        const int line;
        const f_async it;
        const long timeout;

      };

    }
  }
}

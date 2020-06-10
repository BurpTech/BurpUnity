#pragma once

#include <functional>

namespace BddUnity {
  namespace Entry {
    namespace StackedAsyncCallback {

      struct Params {

        using f_done = std::function<void()>;
        using f_async = std::function<void(f_done & done)>;

        const char * label;
        const int line;
        const f_async cb;
        const long timeout;

      };

    }
  }
}

#pragma once

#include <functional>

namespace BddUnity {
  namespace Entry {
    namespace It {

      struct Params {

        using f_testCallback = std::function<void()>;

        const char * should;
        const int line;
        const f_testCallback it;

      };

    }
  }
}

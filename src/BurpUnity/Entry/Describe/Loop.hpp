#pragma once

#include <functional>

namespace BurpUnity {
  namespace Entry {
    namespace Describe {

      struct Loop {

        using f_loop = std::function<void()>;

        const int line;
        const f_loop cb;

      };

    }
  }
}

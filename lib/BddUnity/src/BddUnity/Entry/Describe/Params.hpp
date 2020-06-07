#pragma once

#include <functional>
#include "../../Memory/Interface.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Describe {

      class Instance;

      struct Params {

        using f_describe = std::function<void(Instance & describe)>;

        Memory::Interface & memory;
        const char * thing;
        const int line;
        const f_describe describe;
        const long timeout;

      };

    }
  }
}

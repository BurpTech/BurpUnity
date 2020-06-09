#pragma once

#include <functional>
#include "../Interface.hpp"
#include "../../Depth/Interface.hpp"
#include "../../Memory/Pool/Interface.hpp"
#include "../Pop/Params.hpp"
#include "../Test/Params.hpp"
#include "../It/Params.hpp"
#include "../AsyncIt/Params.hpp"
#include "../Callback/Params.hpp"
#include "../AsyncCallback/Params.hpp"
#include "Setup.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Describe {

      class Instance;

      struct Params {

        using f_describe = std::function<void(Instance & describe)>;

        Depth::Interface & depth;
        Memory::Pool::Interface<Interface, Pop::Params> & popPool;
        Memory::Pool::Interface<Interface, Test::Params> & testPool;
        Memory::Pool::Interface<Interface, It::Params> & itPool;
        Memory::Pool::Interface<Interface, AsyncIt::Params> & asyncItPool;
        Memory::Pool::Interface<Interface, Callback::Params> & callbackPool;
        Memory::Pool::Interface<Interface, AsyncCallback::Params> & asyncCallbackPool;
        Memory::Pool::Interface<Setup, Setup> & setupPool;
        const char * thing;
        const int line;
        const f_describe describe;
        const long timeout;

      };

    }
  }
}

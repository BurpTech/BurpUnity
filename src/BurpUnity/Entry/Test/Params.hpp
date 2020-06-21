#pragma once

#include "../Interface.hpp"
#include "../../Memory/Pool/Interface.hpp"
#include "../StackedAsyncCallback/Params.hpp"
#include "../StackedCallback/Params.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace Test {

      struct Params {
        const char * label;
        const int line;
        Memory::Pool::Interface<Interface, StackedCallback::Params> & stackedCallbackPool;
        Memory::Pool::Interface<Interface, StackedAsyncCallback::Params> & stackedAsyncCallbackPool;
        Interface * entry;
      };

    }
  }
}

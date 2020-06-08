#pragma once

#include "../Interface.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Test {

      struct Params {
        const char * label;
        const int line;
        Memory::Pool::Interface<Interface, Callback::Params> & callbackPool;
        Memory::Pool::Interface<Interface, AsyncCallback::Params> & asyncCallbackPool;
        Interface * entry;
      };

    }
  }
}

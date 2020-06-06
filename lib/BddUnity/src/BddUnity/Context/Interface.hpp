#pragma once

#include <stdio.h>
#include "../Depth/Interface.hpp"
#include "../MemPool/Interface.hpp"

namespace BddUnity {
  namespace Context {

    class Interface {
      public:
        virtual Depth::Interface & getDepth() = 0;
        virtual MemPool::Interface & getDescribeMemPool() = 0;
        virtual MemPool::Interface & getPopMemPool() = 0;
        virtual MemPool::Interface & getItMemPool() = 0;
        virtual MemPool::Interface & getAsyncItMemPool() = 0;
        virtual int snprintParameters(char * buffer, size_t size) = 0;
        virtual int snprintMemory(char * buffer, size_t size) = 0;
    };

  }
}

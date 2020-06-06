#pragma once

#include "../HasError.hpp"

namespace BddUnity {
  namespace MemPool {

    class Interface: public HasError {
      public:
        unsigned long highUsed = 0;
        virtual void * alloc() = 0;
        virtual const Error * free(void * address) = 0;
    };

  }
}

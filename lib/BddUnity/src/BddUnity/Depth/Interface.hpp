#pragma once

#include <stdio.h>
#include "../HasError.hpp"

namespace BddUnity {
  namespace Depth {

    class Interface : public HasError {
      public:
        unsigned long highUsed = 0;
        virtual const Error * free() = 0;
        virtual const Error * push(const char * label, const long timeout) = 0;
        virtual const Error * pop() = 0;
        virtual const char * getLabel(const char * field) = 0;
        virtual const char * getLabel(const char * field1, const char * field2) = 0;
        virtual const long getTimeout(const long timeout) = 0;
        virtual const size_t getMaxDepth() = 0;
    };

  }
}

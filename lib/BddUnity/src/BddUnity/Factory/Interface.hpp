#pragma once

#include "../HasError.hpp"

namespace BddUnity {
  namespace Factory {

    template <class Type, class Params>
    class Interface: public HasError {

      public:

        unsigned long highUsed = 0;
        virtual Type * create(const Params & params) = 0;
        virtual const Error * free(void * address) = 0;

      private:

        void * _alloc();

    };

  }
}

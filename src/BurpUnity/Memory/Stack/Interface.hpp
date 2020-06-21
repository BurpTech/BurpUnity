#pragma once

#include <cstddef>
#include <functional>
#include "../../HasError.hpp"

namespace BurpUnity {
  namespace Memory {
    namespace Stack {

      template <class Type, class Params>
      class Interface: public HasError {

        public:

          using f_each = std::function<const Error * (const Type & item)>;

          unsigned long highUsed = 0;
          virtual const Error * push(const Params & params) = 0;
          virtual const Error * pop() = 0;
          virtual const Error * forEach(f_each each) = 0;
          virtual Type * current() = 0;
          virtual const size_t currentIndex() = 0;
          virtual Type * get(const size_t index) = 0;

        private:

          void * _alloc();

      };

    }
  }
}

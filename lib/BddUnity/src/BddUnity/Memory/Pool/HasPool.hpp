#pragma once

#include "../../HasError.hpp"
#include "Interface.hpp"

namespace BddUnity {
  namespace Memory {
    namespace Pool {

      template <class Type, class Params>
      class HasPool : public HasError {
        
        public:

          HasPool() :
            _pool(nullptr)
          {}

          HasPool(Pool::Interface<Type, Params> * pool) :
            _pool(pool)
          {}

          const Error * free() {
            if (_pool) {
              const Error * e1 = _free();
              if (e1) setError(*e1);
              const Error * e2 = _pool->free(this);
              if (e2) setError(*e2);
            } else {
              setError(Error::Code::NO_POOL);
            }
            return &error;
          }

        protected:

          Pool::Interface<Type, Params> * _pool;

        private:

          virtual const Error * _free() = 0;

      };

    }
  }
}

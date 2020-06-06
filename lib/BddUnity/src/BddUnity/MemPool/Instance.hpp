#pragma once

#include <cstddef>
#include <memory>
#include "Interface.hpp"

namespace BddUnity {
  namespace MemPool {

    template <class T, size_t size, bool safe>
    class Instance: public Interface {

      public:

        void * alloc() override {
          if (_currentUsed == size) {
            setError(Error::Code::MAX_ALLOC);
            return nullptr;
          }

          if (_currentFree) {
            // grab a free address
            return _free[--_currentFree];
          }

          // send the next address from the pool
          void * ret = &(_pool[_currentUsed++]);
          highUsed = _currentUsed > highUsed ? _currentUsed : highUsed;
          return ret;
        }

        const Error * free(void * address) override {
          if (_currentUsed == 0) {
            setError(Error::Code::MIN_ALLOC);
            return &error;
          }


          if (safe) {
            // check that the address has been allocated.
            if (!(
              address >= &(_pool) &&
              address < &(_pool) + (_currentUsed * sizeof(T))
            )) {
              setError(Error::Code::NOT_ALLOC);
              return &error;
            }

            // check that the address has not already been freed
            for (int i = 0; i < _currentFree; i++) {
              if (address == _free[i]) {
                setError(Error::Code::FREED_ADDRESS);
                return &error;
              }
            }
          }

          _currentUsed--;
          _free[_currentFree++] = address;
          return nullptr;
        }

      private:

        std::allocator<T> allocator;
        T * _pool = allocator.allocate(size);
        void * _free[size];
        size_t _currentFree = 0;
        size_t _currentUsed = 0;

    };

  }
}

#pragma once

#include <cstddef>
#include <memory>
#include "./Globals/Error.hpp"

namespace AsyncUnity {

  template <class T, size_t SIZE>
  class MemPool {

    public:

      const Error * error;
      unsigned long highUsed = 0;

      void * alloc() {
        if (_currentUsed == SIZE) {
          error = &Globals::maxAllocError;
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

      const Error * free(void * address) {
        if (_currentUsed == 0) {
          error = &Globals::minAllocError;
          return error;
        }

#if ASYNC_UNITY_SAFE_MEM_POOLS

        // check that the address has been allocated.
        if (!(
          address >= &(_pool) &&
          address < &(_pool) + (_currentUsed * sizeof(T))
        )) {
          return &Globals::notAllocError;
        }

        // check that the address has not already been freed
        for (int i = 0; i < _currentFree; i++) {
          if (address == _free[i]) {
            return &Globals::freedAddressError;
          }
        }

#endif

        _currentUsed--;
        _free[_currentFree++] = address;
        return nullptr;
      }

    private:

      std::allocator<T> allocator;
      T * _pool = allocator.allocate(SIZE);
      void * _free[SIZE];
      size_t _currentFree = 0;
      size_t _currentUsed = 0;

  };

}

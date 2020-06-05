#pragma once

#include <cstddef>
#include <memory>
#include "./Globals/Error.hpp"

namespace AsyncUnity {

  template <class T, size_t SIZE>
  class MemPool {

    public:

      const Error * error;
      size_t highUsed = 0;

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

        // check that the address has not already been freed
        for (int i = 0; i < _currentFree; i++) {
          if (address == _free[i]) {
            return &freedAddressError;
          }
        }

        // check that the address has been allocated.
        //
        // TODO: I'm sure this can be optimized to check if the
        // address falls in the range allocated to the array (up
        // to but not including the _currentUsed entry).
        // Maybe something like:
        //
        //  address >= &(_pool) &&
        //  address < &(_pool) + (_currentUsed * sizeof(T))
        // 
        // But I'm not sure the pointer arithmentic is allowed
        // or if it's portable.
        //
        bool used = false;
        for (int i = _currentUsed - 1; i >= 0; i++) {
          if (address == &(_pool[i])) {
            used = true;
            break;
          }
        }
        if (!used) {
          return &Globals::notAllocError;
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

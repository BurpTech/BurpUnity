#pragma once

#include "../Depth/Instance.hpp"
#include "../MemPool/Instance.hpp"
#include "../Entry/Pop.hpp"
#include "../Entry/Describe.hpp"
#include "../Entry/It.hpp"
#include "../Entry/AsyncIt.hpp"
#include "Interface.hpp"

namespace BddUnity {
  namespace Context {

    template <
      size_t LABEL_BUFFER_SIZE,
      long DEFAULT_TIMEOUT,
      bool SAFE_MEM_POOLS,
      size_t MAX_DEPTH,
      size_t MAX_DESCRIBES,
      size_t MAX_ITS,
      size_t MAX_ASYNC_ITS>
    class Instance : public Interface {

      public:

        Depth::Interface & getDepth() override {
          return _depth;
        }

        MemPool::Interface & getDescribeMemPool() override {
          return _describeMemPool;
        }

        MemPool::Interface & getPopMemPool() override {
          return _popMemPool;
        }

        MemPool::Interface & getItMemPool() override {
          return _itMemPool;
        }

        MemPool::Interface & getAsyncItMemPool() override {
          return _asyncItMemPool;
        }

        int snprintParameters(char * buffer, size_t size) override {

          const char * format = 
            "-----------------------------\n"
            "BddUnity: Context parameters:\n"
            "-----------------------------\n"
            "SAFE_MEM_POOLS: %d\n"
            "MAX_DEPTH: %d\n"
            "LABEL_BUFFER_SIZE: %d\n"
            "DEFAULT_TIMEOUT: %d\n"
            "MAX_DESCRIBES: %d\n"
            "MAX_ITS: %d\n"
            "MAX_ASYNC_ITS: %d\n";

          return snprintf(buffer, size, format,
            SAFE_MEM_POOLS,
            MAX_DEPTH,
            LABEL_BUFFER_SIZE,
            DEFAULT_TIMEOUT,
            MAX_DESCRIBES,
            MAX_ITS,
            MAX_ASYNC_ITS);

        }

        int snprintMemory(char * buffer, size_t size) override {

          const char * format = 
            "------------------------------\n"
            "BddUnity: Actual memory usage:\n"
            "------------------------------\n"
            "maximum depth reached (BDD_UNITY_MAX_DEPTH): %lu (%d)\n"
            "maximum describes allocated (BDD_UNITY_MAX_DESCRIBES): %lu (%d)\n"
            "maximum its allocated (BDD_UNITY_MAX_ITS): %lu (%d)\n"
            "maximum async its allocated (BDD_UNITY_MAX_ASYNC_ITS): %lu (%d)\n";

          return snprintf(buffer, size, format,
            _depth.highUsed,
            MAX_DEPTH,
            _describeMemPool.highUsed,
            MAX_DESCRIBES,
            _popMemPool.highUsed,
            MAX_DEPTH,
            _itMemPool.highUsed,
            MAX_ITS,
            _asyncItMemPool.highUsed,
            MAX_ASYNC_ITS);

        }

      private:

        Depth::Instance<MAX_DEPTH, LABEL_BUFFER_SIZE, DEFAULT_TIMEOUT> _depth;
        MemPool::Instance<Entry::Describe, MAX_DESCRIBES, SAFE_MEM_POOLS> _describeMemPool;
        MemPool::Instance<Entry::Pop, MAX_DEPTH, SAFE_MEM_POOLS> _popMemPool;
        MemPool::Instance<Entry::It, MAX_ITS, SAFE_MEM_POOLS> _itMemPool;
        MemPool::Instance<Entry::AsyncIt, MAX_ASYNC_ITS, SAFE_MEM_POOLS> _asyncItMemPool;

    };

  }
}

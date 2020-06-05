#include "./defines.hpp"
#include "./Globals.hpp"

namespace AsyncUnity {
  namespace Globals {

    int snprintFlags(char * buffer, size_t size) {

      const char * format = 
        "ASYNC_UNITY_SHORT_NAMES: %d\n"
        "ASYNC_UNITY_SAFE_MEM_POOLS: %d\n"
        "ASYNC_UNITY_MAX_DEPTH: %d\n"
        "ASYNC_UNITY_LABEL_BUFFER_SIZE: %d\n"
        "ASYNC_UNITY_DEFAULT_TIMEOUT: %d\n"
        "ASYNC_UNITY_MAX_DESCRIBES: %d\n"
        "ASYNC_UNITY_MAX_ITS: %d\n"
        "ASYNC_UNITY_MAX_ASYNC_ITS: %d\n";

      return snprintf(buffer, size, format,
        ASYNC_UNITY_SHORT_NAMES,
        ASYNC_UNITY_SAFE_MEM_POOLS,
        ASYNC_UNITY_MAX_DEPTH,
        ASYNC_UNITY_LABEL_BUFFER_SIZE,
        ASYNC_UNITY_DEFAULT_TIMEOUT,
        ASYNC_UNITY_MAX_DESCRIBES,
        ASYNC_UNITY_MAX_ITS,
        ASYNC_UNITY_MAX_ASYNC_ITS);

    }

    int snprintMemory(char * buffer, size_t size) {

      const char * format = 
        "MAX_DEPTH: %lu\n"
        "MAX_POPS (should equal MAX_DEPTH): %lu\n"
        "MAX_DESCRIBES: %lu\n"
        "MAX_ITS: %lu\n"
        "MAX_ASYNC_ITS: %lu\n";

      return snprintf(buffer, size, format,
        depth.highUsed,
        describeMemPool.highUsed,
        popMemPool.highUsed,
        itMemPool.highUsed,
        asyncItMemPool.highUsed);

    }

  }
}

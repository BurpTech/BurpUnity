#include "defines.hpp"
#include "Globals.hpp"

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
        "maximum depth reached (ASYNC_UNITY_MAX_DEPTH): %lu (%d)\n"
        "maximum pops allocated (ASYNC_UNITY_MAX_DEPTH): %lu (%d)\n"
        "maximum describes allocated (ASYNC_UNITY_MAX_DESCRIBES): %lu (%d)\n"
        "maximum its allocated (ASYNC_UNITY_MAX_ITS): %lu (%d)\n"
        "maximum async its allocated (ASYNC_UNITY_MAX_ASYNC_ITS): %lu (%d)\n";

      return snprintf(buffer, size, format,
        depth.highUsed,
        ASYNC_UNITY_MAX_DEPTH,
        describeMemPool.highUsed,
        ASYNC_UNITY_MAX_DESCRIBES,
        popMemPool.highUsed,
        ASYNC_UNITY_MAX_DEPTH,
        itMemPool.highUsed,
        ASYNC_UNITY_MAX_ITS,
        asyncItMemPool.highUsed,
        ASYNC_UNITY_MAX_ASYNC_ITS);

    }

  }
}

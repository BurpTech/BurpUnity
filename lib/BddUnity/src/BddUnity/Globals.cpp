#include "defines.hpp"
#include "Globals.hpp"

namespace BddUnity {
  namespace Globals {

    int snprintFlags(char * buffer, size_t size) {

      const char * format = 
        "BDD_UNITY_SHORT_NAMES: %d\n"
        "BDD_UNITY_SAFE_MEM_POOLS: %d\n"
        "BDD_UNITY_MAX_DEPTH: %d\n"
        "BDD_UNITY_LABEL_BUFFER_SIZE: %d\n"
        "BDD_UNITY_DEFAULT_TIMEOUT: %d\n"
        "BDD_UNITY_MAX_DESCRIBES: %d\n"
        "BDD_UNITY_MAX_ITS: %d\n"
        "BDD_UNITY_MAX_ASYNC_ITS: %d\n";

      return snprintf(buffer, size, format,
        BDD_UNITY_SHORT_NAMES,
        BDD_UNITY_SAFE_MEM_POOLS,
        BDD_UNITY_MAX_DEPTH,
        BDD_UNITY_LABEL_BUFFER_SIZE,
        BDD_UNITY_DEFAULT_TIMEOUT,
        BDD_UNITY_MAX_DESCRIBES,
        BDD_UNITY_MAX_ITS,
        BDD_UNITY_MAX_ASYNC_ITS);

    }

    int snprintMemory(char * buffer, size_t size) {

      const char * format = 
        "maximum depth reached (BDD_UNITY_MAX_DEPTH): %lu (%d)\n"
        "maximum pops allocated (BDD_UNITY_MAX_DEPTH): %lu (%d)\n"
        "maximum describes allocated (BDD_UNITY_MAX_DESCRIBES): %lu (%d)\n"
        "maximum its allocated (BDD_UNITY_MAX_ITS): %lu (%d)\n"
        "maximum async its allocated (BDD_UNITY_MAX_ASYNC_ITS): %lu (%d)\n";

      return snprintf(buffer, size, format,
        depth.highUsed,
        BDD_UNITY_MAX_DEPTH,
        describeMemPool.highUsed,
        BDD_UNITY_MAX_DESCRIBES,
        popMemPool.highUsed,
        BDD_UNITY_MAX_DEPTH,
        itMemPool.highUsed,
        BDD_UNITY_MAX_ITS,
        asyncItMemPool.highUsed,
        BDD_UNITY_MAX_ASYNC_ITS);

    }

  }
}

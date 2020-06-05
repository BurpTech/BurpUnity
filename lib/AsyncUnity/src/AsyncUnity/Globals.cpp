#include "./Globals.hpp"

namespace AsyncUnity {
  namespace Globals {

    int snprintMemory(char * buffer, size_t size) {

#ifdef NATIVE
      const char * format = 
        "MAX_DEPTH: %lu\n"
        "MAX_DESCRIBES: %lu\n"
        "MAX_POPS (MAX_DEPTH): %lu\n"
        "MAX_ITS: %lu\n"
        "MAX_ASYNC_ITS: %lu\n";
#else
      const char * format = 
        "MAX_DEPTH: %u\n"
        "MAX_DESCRIBES: %u\n"
        "MAX_POPS (MAX_DEPTH): %u\n"
        "MAX_ITS: %u\n"
        "MAX_ASYNC_ITS: %u\n";
#endif

      return snprintf(buffer, size, format,
        depth.highUsed,
        describeMemPool.highUsed,
        popMemPool.highUsed,
        itMemPool.highUsed,
        asyncItMemPool.highUsed);

    }

  }
}

#include "MemPool.hpp"

namespace BddUnity {
  namespace Globals {

    MemPool<Entry::Describe, BDD_UNITY_MAX_DESCRIBES> describeMemPool;
    MemPool<Entry::Pop, BDD_UNITY_MAX_DEPTH> popMemPool;
    MemPool<Entry::It, BDD_UNITY_MAX_ITS> itMemPool;
    MemPool<Entry::AsyncIt, BDD_UNITY_MAX_ASYNC_ITS> asyncItMemPool;

  }
}

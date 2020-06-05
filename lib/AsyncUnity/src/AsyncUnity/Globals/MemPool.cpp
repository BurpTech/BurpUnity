#include "MemPool.hpp"

namespace AsyncUnity {
  namespace Globals {

    MemPool<Entry::Describe, ASYNC_UNITY_MAX_DESCRIBES> describeMemPool;
    MemPool<Entry::Pop, ASYNC_UNITY_MAX_DEPTH> popMemPool;
    MemPool<Entry::It, ASYNC_UNITY_MAX_ITS> itMemPool;
    MemPool<Entry::AsyncIt, ASYNC_UNITY_MAX_ASYNC_ITS> asyncItMemPool;

  }
}

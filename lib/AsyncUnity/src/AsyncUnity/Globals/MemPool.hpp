#pragma once

#include "../defines.hpp"
#include "../MemPool.hpp"
#include "../Entry/Describe.hpp"
#include "../Entry/Pop.hpp"
#include "../Entry/It.hpp"
#include "../Entry/AsyncIt.hpp"

namespace AsyncUnity {
  namespace Globals {

    extern MemPool<Entry::Describe, ASYNC_UNITY_MAX_DESCRIBES> describeMemPool;
    extern MemPool<Entry::Pop, ASYNC_UNITY_MAX_DEPTH> popMemPool;
    extern MemPool<Entry::It, ASYNC_UNITY_MAX_ITS> itMemPool;
    extern MemPool<Entry::AsyncIt, ASYNC_UNITY_MAX_ASYNC_ITS> asyncItMemPool;
  }
}

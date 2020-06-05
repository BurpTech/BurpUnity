#pragma once

#include "../defines.hpp"
#include "../MemPool.hpp"
#include "../Entry/Describe.hpp"
#include "../Entry/Pop.hpp"
#include "../Entry/It.hpp"
#include "../Entry/AsyncIt.hpp"

namespace BddUnity {
  namespace Globals {

    extern MemPool<Entry::Describe, BDD_UNITY_MAX_DESCRIBES> describeMemPool;
    extern MemPool<Entry::Pop, BDD_UNITY_MAX_DEPTH> popMemPool;
    extern MemPool<Entry::It, BDD_UNITY_MAX_ITS> itMemPool;
    extern MemPool<Entry::AsyncIt, BDD_UNITY_MAX_ASYNC_ITS> asyncItMemPool;
  }
}

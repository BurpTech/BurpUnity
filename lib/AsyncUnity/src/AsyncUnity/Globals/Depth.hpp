#pragma once

#include "../defines.hpp"
#include "../Depth.hpp"

namespace AsyncUnity {
  namespace Globals {

    extern Depth<
      ASYNC_UNITY_MAX_DEPTH,
      ASYNC_UNITY_LABEL_BUFFER_SIZE,
      ASYNC_UNITY_DEFAULT_TIMEOUT> depth;

  }
}

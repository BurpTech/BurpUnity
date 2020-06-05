#include "Depth.hpp"

namespace BddUnity {
  namespace Globals {

    Depth<
      BDD_UNITY_MAX_DEPTH,
      BDD_UNITY_LABEL_BUFFER_SIZE,
      BDD_UNITY_DEFAULT_TIMEOUT> depth;

  }
}

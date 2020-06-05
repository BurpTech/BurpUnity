#pragma once

namespace BddUnity {
  
  class Timeout {
    
    public:

      static constexpr long NO_TIMEOUT = -1;
      static constexpr long INHERIT_TIMEOUT = 0;

      const char * label = nullptr;
      int line = 0;
      long timeout = INHERIT_TIMEOUT;

  };

}

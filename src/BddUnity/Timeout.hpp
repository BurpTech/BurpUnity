#pragma once

#include "HasError.hpp"
namespace BddUnity {
  
  class Timeout : HasError {
    
    public:

      static constexpr long NO_TIMEOUT = -1;
      static constexpr long INHERIT_TIMEOUT = 0;

      const char * label = nullptr;
      int line = 0;
      long timeout = INHERIT_TIMEOUT;

      void start();
      Error * check();

    private:

      unsigned long _started = 0;
      unsigned long _millis();

  };

}

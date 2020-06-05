#pragma once

#include "Error.hpp"

namespace BddUnity {

  class HasStaticError {
    
    public:

      static Error staticError;
      static bool hasStaticError;

      static void setStaticError(const Error::Code code, const char * label, const int line);
      static void setStaticError(const Error::Code code);
      static void setStaticError(const Error & error, const char * label, const int line);
      static void setStaticError(const Error & error);
      static void setStaticError();
      static void unsetStaticError();

  };

}

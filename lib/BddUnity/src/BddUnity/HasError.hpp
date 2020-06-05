#pragma once

#include "Error.hpp"

namespace BddUnity {

  class HasError {
    
    public:

      Error error;
      bool hasError = false;

      void setError(const Error::Code code, const char * label, const int line);
      void setError(const Error::Code code);
      void setError(const Error & error, const char * label, const int line);
      void setError(const Error & error);
      void setError();
      void unsetError();

  };

}

#pragma once

namespace BddUnity {

  class Error {

    public:

      enum class Code {
        NO_ERROR,
        TIMEOUT,
        MAX_DEPTH,
        MIN_DEPTH,
        MAX_ALLOC,
        MIN_ALLOC,
        FREED_ADDRESS,
        NOT_ALLOC
      };

      Code code;
      const char * label;
      int line;

      Error(const Code code, const char * label, const int line);
      Error(const Code code);
      Error(const Error & error, const char * label, const int line);
      Error(const Error & error);
      Error();

      const char * c_str() const;

  };

}

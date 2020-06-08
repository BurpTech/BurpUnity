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
        NOT_ALLOC,
        NO_POOL,
        EMPTY_POOL,
        OUT_OF_BOUNDS,
        BEFORE_SET,
        AFTER_SET,
        BEFORE_EACH_SET,
        AFTER_EACH_SET
      };

      Code code;
      const char * label1;
      const char * label2;
      int line;

      Error(const Code code, const char * label1, const char * label2, const int line);
      Error(const Code code, const char * label, const int line);
      Error(const Code code);
      Error(const Error & error, const char * label1, const char * label2, const int line);
      Error(const Error & error, const char * label, const int line);
      Error(const Error & error);
      Error();

      const char * c_str() const;

  };

}

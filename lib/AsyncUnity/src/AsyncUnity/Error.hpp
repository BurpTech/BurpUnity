#pragma once

namespace AsyncUnity {

  class Error {

    public:

      enum class Code {
        TIMEOUT,
        MAX_DEPTH,
        MIN_DEPTH,
        MAX_ALLOC,
        MIN_ALLOC,
        FREED_ADDRESS,
        NOT_ALLOC
      };

      const Code code;

      Error(Error::Code code);
      const char * c_str() const;

  };

}

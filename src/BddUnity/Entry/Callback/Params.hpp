#pragma once

#include <functional>

namespace BddUnity {
  namespace Entry {
    namespace Callback {

      class Params {

        public:

          using f_callback = std::function<void()>;

          Params(const char * label, const int line, const f_callback cb);
          Params(const Params & params);

          const char * label;
          const int line;
          const f_callback cb;

      };

    }
  }
}

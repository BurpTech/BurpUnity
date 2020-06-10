#pragma once

#include <functional>

namespace BddUnity {
  namespace Entry {
    namespace StackedAsyncCallback {

      class Params {

        public:

          using f_done = std::function<void()>;
          using f_async = std::function<void(f_done & done)>;

          Params(const char * label, const int line, const f_async cb, const long timeout);
          Params(const Params & params);

          const char * label;
          const int line;
          const f_async cb;
          const long timeout;

      };

    }
  }
}

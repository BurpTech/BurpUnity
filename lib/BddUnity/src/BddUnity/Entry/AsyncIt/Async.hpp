#pragma once

#include <functional>
#include "../../Depth/Interface.hpp"

namespace BddUnity {
  namespace Entry {
    namespace AsyncIt {

      class Instance;

      class Async {

        friend class AsyncIt::Instance;

        public:

          using f_testCallback = std::function<void()>;

          void it(const char * should, const f_testCallback it);
          void it(const char * should, const int line, const f_testCallback it);

        private:

          Async();
          Async(Depth::Interface * depth, const char * thing);
          Depth::Interface * _depth;
          const char * _thing;

      };

    }
  }
}

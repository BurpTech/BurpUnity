#pragma once

#include <functional>
#include "../../Memory/Pool/HasPool.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace Describe {

      class Setup : public Memory::Pool::HasPool<Setup, Setup> {

        public:

          using f_setup = std::function<void()>;
          
          Setup(const int line, const f_setup cb);
          Setup(Memory::Pool::Interface<Setup, Setup> * pool, const Setup & setup);
           const Error * free();

          const int line;
          const f_setup cb;

        private:

          const Error * _free() override;

      };

    }
  }
}

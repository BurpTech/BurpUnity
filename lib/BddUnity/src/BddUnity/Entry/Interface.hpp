#pragma once

#include <functional>
#include "../Depth/Interface.hpp"
#include "../Timeout.hpp"

namespace BddUnity {

  class Module;

  namespace Entry {
    namespace Describe {

      class Instance;

    }

    class Interface {

      friend class BddUnity::Module;
      friend class Describe::Instance;

      public:

        using f_done = std::function<void(const Error * error)>;

      private:

        Interface * next = nullptr;

        virtual void _run(Depth::Interface & depth, Timeout & timeout, const f_done & done) = 0;
        virtual const Error * free() = 0;

    };

  }
}

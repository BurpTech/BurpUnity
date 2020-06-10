#pragma once

#include "Params.hpp"
#include "../Interface.hpp"
#include "../../Memory/Pool/HasPool.hpp"

namespace BddUnity {
  namespace Entry {
    namespace StackedAsyncCallback {

      class Instance : public Interface, public Memory::Pool::HasPool<Interface, Params> {

        public:

          Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params);

        private:

          const Params & _params;
          Params::f_done _done;

          void _run(List & list, Depth::Interface & depth, Timeout & timeout, const Interface::f_done & done) override;
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

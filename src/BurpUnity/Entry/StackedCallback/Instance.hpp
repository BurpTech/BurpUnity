#pragma once

#include "../Interface.hpp"
#include "../../Memory/Pool/HasPool.hpp"
#include "Params.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace StackedCallback {

      class Instance : public Interface, public Memory::Pool::HasPool<Interface, Params> {

        public:

          Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params);

        private:

          const Params & _params;

          void _run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) override;
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

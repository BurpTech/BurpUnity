#pragma once

#include "../../Memory/Pool/HasPool.hpp"
#include "../Interface.hpp"
#include "../List.hpp"
#include "Params.hpp"

namespace BurpUnity {
  namespace Entry {
    namespace Test {

      class Instance : public Interface, public Memory::Pool::HasPool<Interface, Params> {

        public:

          Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params);

        private:

          const Params _params;
          List _list;

          void _run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) override;
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

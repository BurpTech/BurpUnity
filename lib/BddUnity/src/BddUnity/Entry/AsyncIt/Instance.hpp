#pragma once

#include "Params.hpp"
#include "Async.hpp"
#include "../Interface.hpp"
#include "../../Factory/HasFactory.hpp"

namespace BddUnity {
  namespace Entry {
    namespace AsyncIt {

      class Instance : public Interface, public Factory::HasFactory<Interface, Params> {

        public:

          Instance(Factory::Interface<Interface, Params> & factory, const Params & params);

        private:

          const Params _params;
          Async _async;
          Params::f_done _done;

          void _run(Depth::Interface & depth, Timeout & timeout, const Interface::f_done & done) override;
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

#pragma once

#include "../Interface.hpp"
#include "../../Factory/HasFactory.hpp"
#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Pop {

      class Instance;
      class Instance : public Interface, public Factory::HasFactory<Interface, Params> {

        public:

          Instance(Factory::Interface<Interface, Params> & factory, const Params & params);

        private:

          void _run(Depth::Interface & depth, Timeout & timeout, const f_done & done) override;
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

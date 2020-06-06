#pragma once

#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    class Pop : public Interface {

      public:

        static Pop * create(Context::Interface & context);
        const Error * free() override;
        void run(Timeout & timeout, const f_done & done) override;

      private:

        Pop(Context::Interface & context);

    };

  }
}

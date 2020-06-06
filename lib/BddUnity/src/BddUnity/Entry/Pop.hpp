#pragma once

#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    class Pop : public Interface {

      friend class Describe;

      private:

        static Pop * create(Context::Interface & context);
        Pop(Context::Interface & context);
        const Error * free() override;
        void run(Timeout & timeout, const f_done & done) override;


    };

  }
}

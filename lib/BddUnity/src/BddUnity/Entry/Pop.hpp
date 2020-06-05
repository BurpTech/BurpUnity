#pragma once

#include "Entry.hpp"

namespace BddUnity {
  namespace Entry {

    class Pop : public Entry {

      public:

        static Pop * create();
        const Error * free() override;
        void run(const f_done & done) override;

    };

  }
}

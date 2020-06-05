#pragma once

#include "./Entry.hpp"

namespace AsyncUnity {
  namespace Entry {

    class Pop : public Entry {

      public:

        static const Error * error;

        static Pop * create();
        const Error * free() override;
        void run(f_done done) override;

    };

  }
}

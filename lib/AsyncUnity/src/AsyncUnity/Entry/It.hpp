#pragma once

#include <unity.h>
#include "./Entry.hpp"

namespace AsyncUnity {
  namespace Entry {

    class It : public Entry {

      public:

        static const Error * error;

        static It * create(const char * should, const int line, const UnityTestFunction it);
        const Error * free() override;
        void run(f_done done) override;

      private:

        const char * _should;
        const int _line;
        const UnityTestFunction _it;

        It(const char * should, const int line, const UnityTestFunction it);

    };

  }
}

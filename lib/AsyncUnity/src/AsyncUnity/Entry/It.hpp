#pragma once

#include <unity.h>
#include "Entry.hpp"

namespace AsyncUnity {
  namespace Entry {

    class It : public Entry {

      public:

        using f_testCallback = std::function<void()>;

        static It * create(const char * should, const int line, const f_testCallback it);
        const Error * free() override;
        void run(const f_done & done) override;

      private:

        const char * _should;
        const int _line;
        const f_testCallback _it;

        It(const char * should, const int line, const f_testCallback it);

    };

  }
}

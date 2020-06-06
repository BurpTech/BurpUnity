#pragma once

#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    class It : public Interface {

      friend class Describe;

      public:

        using f_testCallback = std::function<void()>;

      private:

        const char * _should;
        const int _line;
        const f_testCallback _it;

        static It * create(Context::Interface & context, const char * should, const int line, const f_testCallback it);
        It(Context::Interface & context, const char * should, const int line, const f_testCallback it);
        const Error * free() override;
        void run(Timeout & timeout, const f_done & done) override;

    };

  }
}

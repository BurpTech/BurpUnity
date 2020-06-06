#pragma once

#include <unity.h>
#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    class AsyncIt : public Interface {

      friend class Describe;

      public:

        class Async : public Context::HasContext {

          friend class AsyncIt;

          public:

            using f_testCallback = std::function<void()>;

            void it(const char * should, const f_testCallback it);
            void it(const char * should, const int line, const f_testCallback it);

          private:

            Async(Context::Interface & context, const char * thing);
            const char * _thing;

        };

        using f_done = std::function<void()>;
        using f_async = std::function<void(Async & async, f_done & done)>;

      private:

        static AsyncIt * create(Context::Interface & context, const char * should, const int line, const f_async it, const long timeout);

        const char * _thing;
        const int _line;
        const f_async _it;
        const unsigned long _timeout;

        AsyncIt(Context::Interface & context, const char * thing, const int line, const f_async it, const unsigned long out);
        const Error * free() override;
        void run(Timeout & timeout, const Interface::f_done & done) override;

    };

  }
}

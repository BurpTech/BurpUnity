#pragma once

#include <unity.h>
#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    class AsyncIt : public Interface {

      public:

        class Async : public Context::HasContext {

          public:

            using f_testCallback = std::function<void()>;

            Async();
            Async(Context::Interface & context, const char * thing);
            void it(const char * should, const f_testCallback it);
            void it(const char * should, const int line, const f_testCallback it);

          private:

            const char * _thing;

        };

        using f_done = std::function<void()>;
        using f_async = std::function<void(Async & async, f_done & done)>;

        static AsyncIt * create(Context::Interface & context, const char * should, const int line, const f_async it, const long timeout);

        const Error * free() override;
        void run(Timeout & timeout, const Interface::f_done & done) override;

      private:

        const char * _thing;
        const int _line;
        const f_async _it;
        const unsigned long _timeout;

        AsyncIt(Context::Interface & context, const char * thing, const int line, const f_async it, const unsigned long out);

    };

  }
}

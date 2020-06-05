#pragma once

#include <unity.h>
#include "Entry.hpp"

namespace AsyncUnity {
  namespace Entry {

    class AsyncIt : public Entry {

      public:

        class Async {

          public:

            using f_testCallback = std::function<void()>;

            Async();
            Async(const char * thing);
            void it(const char * should, const f_testCallback it);
            void it(const char * should, const int line, const f_testCallback it);

          private:

            const char * _thing;

        };

        using f_done = std::function<void()>;
        using f_async = std::function<void(Async & async, f_done & done)>;

        static AsyncIt * create(const char * should, const int line, const f_async it, const long timeout);

        const Error * free() override;
        void run(const Entry::f_done & done) override;

      private:

        const char * _thing;
        const int _line;
        const f_async _it;
        const unsigned long _timeout;

        AsyncIt(const char * thing, const int line, const f_async it, const unsigned long out);

    };

  }
}

#pragma once

#include <unity.h>
#include "./Entry.hpp"

namespace AsyncUnity {
  namespace Entry {

    class AsyncIt : public Entry {

      public:

        using f_test = std::function<void(const char * label, const int line, UnityTestFunction cb)>;
        using f_async = std::function<void(f_done done, f_test test)>;

        static const Error * error;

        static AsyncIt * create(const char * should, const int line, const f_async it, const long timeout);

        const Error * free() override;
        void run(f_done done) override;

      private:

        const char * _should;
        const int _line;
        const f_async _it;
        const unsigned long _timeout;

        AsyncIt(const char * should, const int line, const f_async it, const unsigned long out);

    };

  }
}

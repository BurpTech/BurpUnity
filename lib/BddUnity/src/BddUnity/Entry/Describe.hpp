#pragma once

#include <unity.h>
#include <functional>
#include "../Timeout.hpp"
#include "../Error.hpp"
#include "../HasError.hpp"
#include "Entry.hpp"
#include "It.hpp"
#include "AsyncIt.hpp"

namespace BddUnity {
  namespace Entry {

    class Describe : public Entry, public HasError {

      public:

        using f_describe = std::function<void(Describe & describe)>;

        static Describe * create(const char * thing, const int line, const f_describe describe, unsigned long timeout);

        const Error * free() override;
        void describe(const char * thing, const f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);
        void describe(const char * thing, const int line, const f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);
        void async(const char * should, const AsyncIt::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);
        void async(const char * should, const int line, const AsyncIt::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);
        void it(const char * should, const It::f_testCallback it);
        void it(const char * should, const int line, const It::f_testCallback it);
        void run(const f_done & done) override;

      private:

        const char * _thing;
        const int _line;
        const f_describe _describe;
        const unsigned long _timeout;
        Entry * _entries = nullptr;
        Entry * _entriesTail = nullptr;
        const Error * _error = nullptr;

        Describe(const char * thing, const int line, const f_describe describe, unsigned long timeout);
        void _append(Entry * entry);
        void _reportError(const char * field, const int line);

    };

  }
}

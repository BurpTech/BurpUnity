#pragma once

#include <unity.h>
#include "./Entry.hpp"

namespace AsyncUnity {

  class It : public Entry {

    public:

      using f_done = std::function<void()>;
      using f_test = std::function<void(const char * label, const int line, UnityTestFunction cb)>;
      using f_async = std::function<void(f_done done, f_test test)>;

      const char * should;
      const int line;
      const UnityTestFunction sync;
      const f_async async;
      const unsigned long timeout;

      It(const char * should, const int line, const f_async cb, const unsigned long timeout = 0) :
        Entry(Type::IT),
        should(should),
        line(line),
        sync(nullptr),
        async(cb),
        timeout(timeout) {}

      It(const char * should, const int line, const UnityTestFunction cb) :
        Entry(Type::IT),
        should(should),
        line(line),
        sync(cb),
        async(nullptr),
        timeout(0) {}

  };

}

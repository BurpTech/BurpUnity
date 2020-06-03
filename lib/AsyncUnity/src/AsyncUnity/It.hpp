#pragma once

#include <unity.h>
#include "./Entry.hpp"

namespace AsyncUnity {

  class It : public Entry {

    public:

      const char * should;
      const int line;
      const UnityTestFunction cb;

      It(const char * should, const int line, const UnityTestFunction cb) :
        Entry(Type::IT),
        should(should),
        line(line),
        cb(cb) {}

  };

}

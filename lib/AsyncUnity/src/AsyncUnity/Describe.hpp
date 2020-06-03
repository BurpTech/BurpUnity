#pragma once

#include <unity.h>
#include <functional>
#include "./Entry.hpp"
#include "./It.hpp"

namespace AsyncUnity {

  class Describe : public Entry {

    public:

      using f_describe = std::function<void(Describe * entry)>;

      const char * thing;
      f_describe cb;
      Entry * entries;

      Describe(const char * thing, const f_describe cb) :
        Entry(Type::DESCRIBE),
        thing(thing),
        cb(cb),
        entries(nullptr),
        _entriesTail(nullptr) {}

      void describe(const char * thing, const f_describe cb) {
        Describe * entry = new Describe(thing, cb);
        if (entries) {
          _entriesTail->next = entry;
        } else {
          entries = entry;
        }
        _entriesTail = entry;
      }

      void it(const char * should, const int line, const UnityTestFunction cb) {
        It * entry = new It(should, line, cb);
        if (entries) {
          _entriesTail->next = entry;
        } else {
          entries = entry;
        }
        _entriesTail = entry;
      }

    private:

      Entry * _entriesTail;

  };

}

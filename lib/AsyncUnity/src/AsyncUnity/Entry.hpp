#pragma once

#include "./Type.hpp"

namespace AsyncUnity {

  class Entry {

    public:

      const Type type;
      Entry * next;

      Entry(Type type) :
        type(type),
        next(nullptr) {}

      template <class T>
      T * as() {
        return static_cast<T*>(this);
      }

  };

}

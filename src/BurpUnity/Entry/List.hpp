#pragma once

#include "Interface.hpp"
#include "../Error.hpp"
#include <cstddef>

namespace BurpUnity {
  namespace Entry {

    class List {

      public:

        Interface * head;

        List();
        void append(Interface * entry);
        void append(List & source);
        void transfer(List & destination);
        void prepend(Interface * entry);
        void prepend(List & source);
        const Error * freeHead();
        const Error * freeAll();

      private:

        Interface * _tail;
        size_t _length;

    };

  }
}

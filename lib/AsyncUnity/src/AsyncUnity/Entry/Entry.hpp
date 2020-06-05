#pragma once

#include <functional>
#include "../Error.hpp"

namespace AsyncUnity {
  namespace Entry {

    class Entry {

      public:

        bool timedOut = false;

        using f_done = std::function<void(const Error * error)>;

        Entry * next = nullptr;

        // The global timeout structure should be populated with 
        // the timeout parameters, for the purposes of creating
        // a timeout error
        virtual void run(f_done done) = 0;

        virtual const Error * free() = 0;
    };

  }
}

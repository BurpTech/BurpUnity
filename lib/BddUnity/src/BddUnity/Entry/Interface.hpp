#pragma once

#include <functional>
#include "../Timeout.hpp"
#include "../HasStaticError.hpp"
#include "../Context/HasContext.hpp"

namespace BddUnity {
  namespace Entry {

    class Interface : public HasStaticError, public Context::HasContext {

      public:

        bool timedOut = false;

        using f_done = std::function<void(const Error * error)>;

        Interface * next = nullptr;

        // The global timeout structure should be populated with 
        // the timeout parameters, for the purposes of creating
        // a timeout error
        virtual void run(Timeout & timeout, const f_done & done) = 0;

        virtual const Error * free() = 0;

      protected:

        Interface(Context::Interface & context);

    };

  }
}

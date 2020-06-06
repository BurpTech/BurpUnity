#pragma once

#include <functional>
#include "../Timeout.hpp"
#include "../HasStaticError.hpp"
#include "../Context/HasContext.hpp"

namespace BddUnity {

  class Module;

  namespace Entry {

    class Interface : public HasStaticError, public Context::HasContext {

      friend class BddUnity::Module;
      friend class Describe;

      public:

        using f_done = std::function<void(const Error * error)>;

      protected:

        Interface(Context::Interface & context);

      private:

        Interface * next = nullptr;
        
        virtual void run(Timeout & timeout, const f_done & done) = 0;
        virtual const Error * free() = 0;

    };

  }
}

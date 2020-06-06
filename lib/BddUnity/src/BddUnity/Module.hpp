#pragma once

#include "HasError.hpp"
#include "Context/HasContext.hpp"
#include "Entry/Interface.hpp"
#include "Entry/Describe.hpp"
#include "Timeout.hpp"

namespace BddUnity {

  class Module : public HasError, public Context::HasContext {
    
    public:

      Module(
        Context::Interface & context,
        const char * name,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      Module(
        Context::Interface & context,
        const char * name,
        const int line,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      void loop();
      const bool isRunning();

    private:

      enum class State {
        READY,
        WAITING,
        FINISHED
      };

      Entry::Interface * _entries;
      Timeout _timeout;
      State _state = State::READY;
      unsigned long _count = 0;

      void _next();
      void _done(const unsigned long count, const Error * e);
      void _end();

  };

}

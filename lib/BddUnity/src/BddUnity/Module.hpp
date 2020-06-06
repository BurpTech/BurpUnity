#pragma once

#include "Context/Interface.hpp"
#include "Entry/Interface.hpp"
#include "Entry/Describe.hpp"
#include "Timeout.hpp"
#include "HasError.hpp"

namespace BddUnity {

  class Module : public HasError {
    
    public:

      Module(
        Context::Interface & context,
        const char * thing,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      Module(
        Context::Interface & context,
        const char * thing,
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

      Timeout _timeout;
      Context::Interface & _context;
      Entry::Interface * _entries;
      State _state = State::READY;
      unsigned long _count = 0;
      unsigned long _started = 0;

      void _next();
      void _checkTimeout();
      void _done(const unsigned long count, const Error * e);
      void _end();
      unsigned long _millis();

  };

}

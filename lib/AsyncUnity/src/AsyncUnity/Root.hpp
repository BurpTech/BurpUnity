#pragma once

#include "Entry/Describe.hpp"
#include "Timeout.hpp"
#include "HasError.hpp"

namespace AsyncUnity {

  class Root : public HasError {
    
    public:

      int status = 0;

      Root(
        const char * thing,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      Root(
        const char * file,
        const char * thing,
        const int line,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      void start();
      void loop();
      const bool isRunning();

    private:

      enum class State {
        READY,
        WAITING,
        FINISHED
      };

      const char * _file;
      Entry::Entry * _entries;
      State _state = State::READY;
      unsigned long _count = 0;
      long _timeout = 0;
      unsigned long _started = 0;

      void _next();
      void _checkTimeout();
      void _done(const unsigned long count, const Error * e);
      void _end();
      unsigned long _millis();

  };

}

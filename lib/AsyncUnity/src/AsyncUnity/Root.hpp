#pragma once

#include "./Entry/Describe.hpp"
#include "Timeout.hpp"

namespace AsyncUnity {

  class Root {
    
    public:

      const Error * error = nullptr;
      int status = 0;

      Root(
        const char * file,
        const char * thing,
        const int line,
        Entry::Describe::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      void setup();
      void loop();
      bool isRunning();

    private:

      enum class State {
        NEXT,
        WAITING,
        DONE,
        FINISHED
      };

      const char * _file;
      Entry::Entry * _entries;
      State _state = State::NEXT;
      long _timeout = 0;
      unsigned long _started = 0;

      void _end();
      unsigned long _millis();

  };

}

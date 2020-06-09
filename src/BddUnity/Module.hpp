#pragma once

#include "HasError.hpp"
#include "Memory/Interface.hpp"
#include "Depth/Interface.hpp"
#include "Entry/List.hpp"
#include "Entry/Describe/Params.hpp"
#include "Timeout.hpp"
#include <cstddef>

namespace BddUnity {

  class Module : public HasError {
    
    public:

      Module(
        Memory::Interface & memory,
        const char * name,
        Entry::Describe::Params::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      Module(
        Memory::Interface & memory,
        const char * name,
        const int line,
        Entry::Describe::Params::f_describe cb,
        long timeout = Timeout::INHERIT_TIMEOUT
      );
      ~Module();
      void loop();
      const bool isRunning();
      int snprintMaxDepth(char * buffer, size_t size);

    private:

      enum class State {
        READY,
        WAITING,
        FINISHED
      };

      Depth::Interface * _depth;
    public:
      Entry::List _list;
    private:
      Timeout _timeout;
      State _state = State::READY;
      unsigned long _count = 0;

      void _next();
      void _done(const unsigned long count, const Error * e);
      void _reportError(const Error * e);
      void _end();

  };

}

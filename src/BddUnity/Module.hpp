#pragma once

#include <functional>
#include "Entry/Interface.hpp"
#include "HasError.hpp"
#include "Runnable.hpp"
#include "Depth/Interface.hpp"
#include "Entry/List.hpp"
#include "Entry/Describe/Params.hpp"
#include "Timeout.hpp"
#include <cstddef>

namespace BddUnity {

  class Module : public Runnable {

    friend class Entry::Describe::Instance;
    
    public:

      Module(
        const char * name,
        Entry::Describe::Params::f_describe cb,
        const long timeout = Timeout::INHERIT_TIMEOUT
      );
      Module(
        const char * name,
        const int line,
        Entry::Describe::Params::f_describe cb,
        const long timeout = Timeout::INHERIT_TIMEOUT
      );
      ~Module();
      void setup(Memory::Interface & memory) override;
      void loop() override;
      Runnable::State getState() override;

      int snprintMaxDepth(char * buffer, size_t size);

    private:

      using f_include = std::function<void(
        const char * name,
        const int line,
        const Entry::Describe::Params::f_describe cb,
        const long timeout
      )>;

      enum class State {
        IDLE,
        READY,
        WAITING,
        FINISHED
      };

      const char * _name;
      const int _line;
      Entry::Describe::Params::f_describe _cb;
      const long _timeout;
      Depth::Interface * _depth;
      Entry::List _list;
      Timeout _currentTimeout;
      State _state;
      unsigned long _count = 0;

      void _next();
      void _done(const unsigned long count, const Error * e);
      void _reportError(const Error & e);
      void _end();
      void _include(f_include include);

  };

}

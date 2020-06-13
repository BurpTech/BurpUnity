#include "Module.hpp"

#include <unity.h>
#include "Depth/Interface.hpp"
#include "Entry/Interface.hpp"
#include "Error.hpp"
#include "Globals.hpp"
#include "Entry/Describe/Params.hpp"
#include "Depth/Params.hpp"
#include "Memory/Interface.hpp"
#include "Memory/Pool/Interface.hpp"
#include "Runnable.hpp"

namespace BddUnity {

  using namespace std::placeholders;

  Module::Module(
    const char * name,
    Entry::Describe::Params::f_describe cb,
    const long timeout
  ) :
    Module(name, 0, cb, timeout)
  {}

  Module::Module(
    const char * name,
    const int line,
    Entry::Describe::Params::f_describe cb,
    const long timeout
  ) :
    _name(name),
    _line(line),
    _cb(cb),
    _timeout(timeout),
    _state(State::IDLE)
  {}

  Module::~Module() {
    _list.freeAll();
    if (_depth) {
      _depth->free();
    }
  }

  void Module::_include(f_include include) {
    include(_name, _line, _cb, _timeout);
  }

  void Module::setup(Memory::Interface & memory) {
    Memory::Pool::Interface<Depth::Interface, Depth::Params> & depthPool = memory.getDepthPool();
    const Depth::Params depthParams = {};
    _depth = depthPool.create(depthParams);
    if (!_depth) {
      _reportError(depthPool.error);
      return;
    }
    Memory::Pool::Interface<Entry::Interface, Entry::Describe::Params> & describePool = memory.getDescribePool();
    const Entry::Describe::Params describeParams = {
      *_depth,
      memory.getPopPool(),
      memory.getTestPool(),
      memory.getItPool(),
      memory.getAsyncItPool(),
      memory.getCallbackPool(),
      memory.getAsyncCallbackPool(),
      memory.getStackedCallbackPool(),
      memory.getStackedAsyncCallbackPool(),
      memory.getSetupPool(),
      _name,
      _line,
      _cb,
      _timeout
    };
    Entry::Interface * entry = describePool.create(describeParams);
    if (!entry) {
      _reportError(describePool.error);
      return;
    }
    _list.append(entry);
    _state = State::READY;
  }

  void Module::loop() {
    if (isRunning()) {
      _depth->loop();
      switch (_state) {
        case State::WAITING:
          {
            Error * e = _currentTimeout.check();
            if (e) {
              _done(_count, e);
            }
          }
          break;
        case State::READY:
          _next();
          break;
        case State::IDLE:
        case State::FINISHED:
          // // do nothing but this avoids
          // // compiler warnings
          break;
      }
    }
  }

  Runnable::State Module::getState() {
    switch (_state) {
      case State::IDLE:
        return Runnable::State::IDLE;
      case State::READY:
      case State::WAITING:
        return Runnable::State::RUNNING;
      case State::FINISHED:
        // do nothing but this avoids
        // compiler warnings
        break;
    }
    return Runnable::State::FINISHED;
  }

  void Module::_next() {
    Entry::Interface * entry = _list.head;
    if (entry) {
      _currentTimeout.start();
      _count++;
      _state = State::WAITING;
      entry->_run(_list, *_depth, _currentTimeout, std::bind(&Module::_done, this, _count, _1));
    } else {
      _end();
    }
  }

  const Depth::Usage Module::getUsage() const {
    return _usage;
  }

  void Module::_done(const unsigned long count, const Error * e) {
    // ignore the call if no longer running or the
    // count is different to the current count.
    // This would mean that we moved on already,
    // probably due to a timeout or the user calling
    // done multiple times
    if (isRunning() && _count == count) {
      // Check for errors and update _entries
      // appropriately
      if (e) {
        _reportError(*e);
        return;
      }
      // all fine, line up the next entry and free
      // the previous one
      const Error * e = _list.freeHead();
      if (e) {
        _reportError(*e);
        return;
      }
      // still fine set the state to READY
      _state = State::READY;
    }
  }

  void Module::_reportError(const Error & e) {
    // store the error for users to read later
    if (e.label1) {
      setError(e);
    } else {
      setError(e, _name, _line);
    }
    // report the error
    const char * label;
    if (error.label2) {
      label = _depth->getLabel(error.label1, error.label2);
    } else {
      label = _depth->getLabel(error.label1);
    }
    Globals::errorLine = error.line;
    Globals::errorMessage = error.c_str();
    UnityDefaultTestRun([]() {
      UNITY_TEST_FAIL(Globals::errorLine, Globals::errorMessage);
    }, label, error.line);
    // Clean everything up and stop
    _list.freeAll();
    _end();
  }

  void Module::_end() {
    if (_depth) {
      _usage = _depth->getUsage();
      _depth->free();
      _depth = nullptr;
    }
    _state = State::FINISHED;
  }

}

#include "Module.hpp"

#include <chrono>
#include <unity.h>
#include "Context/Interface.hpp"
#include "defines.hpp"
#include "Globals.hpp"
#include "Error.hpp"

namespace BddUnity {

  using namespace std::placeholders;

  Module::Module(
    Context::Interface & context,
    const char * thing,
    Entry::Describe::f_describe cb,
    long timeout
  ) :
    Module(context, thing, 0, cb, timeout)
  {}

  Module::Module(
    Context::Interface & context,
    const char * thing,
    const int line,
    Entry::Describe::f_describe cb,
    long timeout
  ) :
    _context(context),
    _entries(Entry::Describe::create(context, thing, line, cb, timeout))
  {}

  void Module::loop() {
    switch (_state) {
      case State::FINISHED:
        //do nothing
        break;
      case State::WAITING:
        _checkTimeout();
        break;
      case State::READY:
        _next();
        break;
    }
  }

  const bool Module::isRunning() {
    return (_state != State::FINISHED);
  }

  void Module::_next() {
    Entry::Interface * entry = _entries;
    if (entry) {
      _started = _millis();
      _count++;
      _state = State::WAITING;
      entry->run(_timeout, std::bind(&Module::_done, this, _count, _1));
    } else {
      _end();
    }
  }

  void Module::_checkTimeout() {
    if (_timeout.timeout != Timeout::NO_TIMEOUT) {
      if (_millis() - _started > static_cast<unsigned long>(_timeout.timeout)) {
        Error e(Error::Code::TIMEOUT, _timeout.label, _timeout.line);
        _done(_count, &e);
      }
    }
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
        // store the error for users to read later
        setError(*e);
        // report the error
        const char * label = _context.getDepth().getLabel(error.label);
        Globals::errorLine = error.line;
        Globals::errorMessage = error.c_str();
        UnityDefaultTestRun([]() {
          UNITY_TEST_FAIL(Globals::errorLine, Globals::errorMessage);
        }, label, error.line);
        // Clean everything up and stop
        while (_entries) {
          _entries->free();
          _entries = _entries->next;
        }
        _end();
      } else {
        // all fine, line up the next entry and free
        // the previous one
        Entry::Interface * previous = _entries;
        _entries = _entries->next;
        previous->free();
        _state = State::READY;
      }
    }
  }

  void Module::_end() {
    _state = State::FINISHED;
  }

  unsigned long Module::_millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  }

}

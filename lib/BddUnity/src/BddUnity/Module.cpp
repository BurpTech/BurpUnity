#include "Module.hpp"

#include <chrono>
#include <unity.h>
#include "defines.hpp"
#include "Globals.hpp"
#include "Globals/TestParams.hpp"
#include "Error.hpp"

namespace BddUnity {

  using namespace std::placeholders;

  Module::Module(
    const char * thing,
    Entry::Describe::f_describe cb,
    long timeout
  ) :
    _file(thing),
    _entries(Entry::Describe::create(thing, 0, cb, timeout))
  {}

  Module::Module(
    const char * file,
    const char * thing,
    const int line,
    Entry::Describe::f_describe cb,
    long timeout
  ) :
    _file(file),
    _entries(Entry::Describe::create(thing, line, cb, timeout))
  {}

  void Module::start() {
    UnityBegin(_file);

#if BDD_UNITY_PRINT_REPORT > 0
    // Print the build flags
    size_t size = 256;
    char buffer[size];
    puts("----------------------\n");
    puts("BddUnity: Build flags:\n");
    puts("----------------------\n");
    BddUnity::Globals::snprintFlags(buffer, size);
    puts(buffer);
#endif

    _next();
  }

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
    Entry::Entry * entry = _entries;
    if (entry) {
      _started = _millis();
      _count++;
      _state = State::WAITING;
      entry->run(std::bind(&Module::_done, this, _count, _1));
    } else {
      _end();
    }
  }

  void Module::_checkTimeout() {
    if (Globals::timeout.timeout != Timeout::NO_TIMEOUT) {
      if (_millis() - _started > static_cast<unsigned long>(Globals::timeout.timeout)) {
        Error e(Error::Code::TIMEOUT, Globals::timeout.label, Globals::timeout.line);
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
        const char * label = Globals::depth.getLabel(error.label);
        Globals::testLine = error.line;
        Globals::testMessage = error.c_str();
        UnityDefaultTestRun([]() {
          UNITY_TEST_FAIL(Globals::testLine, Globals::testMessage);
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
        Entry::Entry * previous = _entries;
        _entries = _entries->next;
        previous->free();
        _state = State::READY;
      }
    }
  }

  void Module::_end() {

#if BDD_UNITY_PRINT_REPORT > 0
    // Print the actual memory usage for tuning
    size_t size = 512;
    char buffer[size];
    puts("------------------------------\n");
    puts("BddUnity: Actual memory usage:\n");
    puts("------------------------------\n");
    BddUnity::Globals::snprintMemory(buffer, size);
    puts(buffer);
#endif

    _state = State::FINISHED;
    status = UnityEnd();
  }

  unsigned long Module::_millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  }

}

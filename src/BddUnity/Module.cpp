#include "Module.hpp"

#include <unity.h>
#include "Entry/Interface.hpp"
#include "Globals.hpp"
#include "Entry/Describe/Params.hpp"
#include "Depth/Params.hpp"

namespace BddUnity {

  using namespace std::placeholders;

  Module::Module(
    Memory::Interface & memory,
    const char * name,
    Entry::Describe::Params::f_describe cb,
    long timeout
  ) :
    Module(memory, name, 0, cb, timeout)
  {}

  Module::Module(
    Memory::Interface & memory,
    const char * name,
    const int line,
    Entry::Describe::Params::f_describe cb,
    long timeout
  ) {
    const Depth::Params depthParams = {};
    _depth = memory.getDepthPool().create(depthParams);
    const Entry::Describe::Params describeParams = {
      *_depth,
      memory.getPopPool(),
      memory.getTestPool(),
      memory.getItPool(),
      memory.getAsyncItPool(),
      memory.getCallbackPool(),
      memory.getAsyncCallbackPool(),
      memory.getSetupPool(),
      name,
      line,
      cb,
      timeout
    };
    _list.append(memory.getDescribePool().create(describeParams));
  }

  Module::~Module() {
    _list.freeAll();
    _depth->free();
  }

  void Module::loop() {
    if (isRunning()) {
      _depth->loop();
      switch (_state) {
        case State::FINISHED:
          //do nothing
          break;
        case State::WAITING:
          {
            Error * e = _timeout.check();
            if (e) {
              _done(_count, e);
            }
          }
          break;
        case State::READY:
          _next();
          break;
      }
    }
  }

  const bool Module::isRunning() {
    return (_state != State::FINISHED);
  }

  void Module::_next() {
    Entry::Interface * entry = _list.head;
    if (entry) {
      _timeout.start();
      _count++;
      _state = State::WAITING;
      entry->_run(_list, *_depth, _timeout, std::bind(&Module::_done, this, _count, _1));
    } else {
      _end();
    }
  }

  int Module::snprintMaxDepth(char * buffer, size_t size) {

    const char * format = 
      "--------------------\n"
      "BddUnity: max depth:\n"
      "--------------------\n"
      "maximum depth reached (BDD_UNITY_MAX_DEPTH): %lu (%d)\n";

    return snprintf(buffer, size, format,
      _depth->highUsed,
      _depth->getMaxDepth());

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
        _reportError(e);
        return;
      }
      // all fine, line up the next entry and free
      // the previous one
      const Error * e = _list.freeHead();
      if (e) {
        _reportError(e);
        return;
      }
      // still fine set the state to READY
      _state = State::READY;
    }
  }

  void Module::_reportError(const Error * e) {
    // store the error for users to read later
    setError(*e);
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
    _state = State::FINISHED;
  }

}

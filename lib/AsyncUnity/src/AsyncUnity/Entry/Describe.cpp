#include "./Describe.hpp"
#include "../Globals.hpp"
#include "./AsyncIt.hpp"
#include "./It.hpp"
#include "./Pop.hpp"

namespace AsyncUnity {
  namespace Entry {

    const Error * Describe::error = nullptr;

    Describe * Describe::create(const char * thing, const int line, const f_describe describe, unsigned long timeout) {
      void * address = Globals::describeMemPool.alloc();
      if (address) {
        return new(address) Describe(thing, line, describe, timeout);
      }
      error = Globals::describeMemPool.error;
      return nullptr;
    }

    const Error * Describe::free() {
      const Error * ret = nullptr;
      const Error * e = nullptr;
      while (_entries) {
        e = _entries->free();
        if (e) ret = e;
        _entries = _entries->next;
      }
      e = Globals::describeMemPool.free(this);
      if (e) ret = e;
      return ret;
    }

    void Describe::describe(const char * thing, const int line, const f_describe describe, const long timeout) {
      Describe * entry = Describe::create(thing, line, describe, timeout);
      if (entry) {
        _append(entry);
      } else {
        _error = Describe::error;
        _reportError(thing, line);
      }
    }

    void Describe::it(const char * should, const int line, const AsyncIt::f_async it, const long timeout) {
      AsyncIt * entry = AsyncIt::create(should, line, it, timeout);
      if (entry) {
        _append(entry);
      } else {
        _error = AsyncIt::error;
        _reportError(should, line);
      }
    }

    void Describe::it(const char * should, const int line, const UnityTestFunction it) {
      It * entry = It::create(should, line, it);
      if (entry) {
        _append(entry);
      } else {
        _error = It::error;
        _reportError(should, line);
      }
    }

    void Describe::run(f_done done) {
      Globals::timeout.timeout = Timeout::NO_TIMEOUT;
      const Error * e = Globals::depth.push(_thing, _timeout);
      if (e) {
        // failed to increase the depth
        done(e);
        return;
      }

      // collect the new entries
      _describe(this);

      // check for error (eg: from MemPool allocation)
      if (_error) {
        done(_error);
        return;
      }

      // append a pop to the entries
      Pop * pop = Pop::create();
      if (!pop) {
        // I don't think this can happen
        // as the depth would be exceeded first
        _reportError("pop depth", _line);
        done(Pop::error);
        return;
      }
      _append(pop);

      // now insert the entries as next
      // and clear the local reference
      _entriesTail->next = next;
      next = _entries;
      _entries = nullptr;

      // and we're done
      done(nullptr);
      return;
    }

    Describe::Describe(
        const char * thing,
        const int line,
        const f_describe describe,
        unsigned long timeout) :
      _thing(thing),
      _line(line),
      _describe(describe),
      _timeout(timeout) {}

    void Describe::_append(Entry * entry) {
      if (_entries) {
        _entriesTail->next = entry;
      } else {
        _entries = entry;
      }
      _entriesTail = entry;
    }

    void Describe::_reportError(const char * field, const int line) {
      const char * label = Globals::depth.getLabel(field);
      Globals::testMessage = _error->c_str();
      Globals::testLine = line;
      UnityDefaultTestRun([]() {
        UNITY_TEST_FAIL(Globals::testLine, Globals::testMessage);
      }, label, line);
    }

  }
}

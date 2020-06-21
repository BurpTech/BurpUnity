#include "Error.hpp"

namespace BurpUnity {

  Error::Error(const Error::Code code, const char * label1, const char * label2, const int line) :
    code(code),
    label1(label1),
    label2(label2),
    line(line) {}

  Error::Error(const Error::Code code, const char * label, const int line) :
    Error(code, label, nullptr, line) {}

  Error::Error(const Error::Code code) :
    Error(code, nullptr, nullptr, 0) {}

  Error::Error(const Error & error, const char * label, const int line) :
    Error(error.code, label, nullptr, line) {}

  Error::Error(const Error & error, const char * label1, const char * label2, const int line) :
    Error(error.code, label1, label2, line) {}

  Error::Error(const Error & error) :
    Error(error.code, error.label1, error.label2, error.line) {}

  Error::Error() :
    Error(Error::Code::NO_ERROR, nullptr, nullptr, 0) {}

  const char * Error::c_str() const {
    switch (code) {
      case Code::NO_ERROR:
        return "no error";
      case Code::TIMEOUT:
        return "timed out";
      case Code::MAX_DEPTH:
        return "maximum depth exceeded";
      case Code::MIN_DEPTH:
        return "reducing depth when at zero depth";
      case Code::MAX_ALLOC:
        return "maximum allocations exceeded";
      case Code::MIN_ALLOC:
        return "releasing allocation when nothing allocated";
      case Code::FREED_ADDRESS:
        return "releasing allocation that was already released";
      case Code::NOT_ALLOC:
        return "releasing allocation that was not allocated yet";
      case Code::NO_POOL:
        return "trying to release an instance that was not allocated from a pool";
      case Code::EMPTY_POOL:
        return "trying to get the current item in an empty stack";
      case Code::OUT_OF_BOUNDS:
        return "index out of bounds";
      case Code::BEFORE_SET:
        return "before callback can only be set once per describe";
      case Code::AFTER_SET:
        return "after callback can only be set once per describe";
      case Code::BEFORE_EACH_SET:
        return "beforeEach callback can only be set once per describe";
      case Code::AFTER_EACH_SET:
        return "afterEach callback can only be set once per describe";
      case Code::HAS_SETUP:
        return "setup callback can only be set once per describe";
      case Code::HAS_LOOP:
        return "loop callback can only be set once per describe";
    }
    return nullptr;
  }

}

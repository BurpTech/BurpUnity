#include "Error.hpp"

namespace AsyncUnity {

  Error::Error(const Error::Code code, const char * label, const int line) :
    code(code),
    label(label),
    line(line) {}

  Error::Error(const Error::Code code) :
    Error(code, nullptr, 0) {}

  Error::Error(const Error & error, const char * label, const int line) :
    Error(error.code, label, line) {}

  Error::Error(const Error & error) :
    Error(error.code, error.label, error.line) {}

  Error::Error() :
    Error(Error::Code::NO_ERROR, nullptr, 0) {}

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
    }
    return nullptr;
  }

}

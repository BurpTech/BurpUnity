#include "./Error.hpp"

namespace AsyncUnity {

  Error::Error(Error::Code code) :
    code(code) {}

  const char * Error::c_str() const {
    switch (code) {
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
  }

}

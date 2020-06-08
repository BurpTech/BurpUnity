#include <chrono>
#include "Timeout.hpp"

namespace BddUnity {

  void Timeout::start() {
    _started = _millis();
  }

  Error * Timeout::check() {
    if (timeout != Timeout::NO_TIMEOUT) {
      if (_millis() - _started > static_cast<unsigned long>(timeout)) {
        setError(Error::Code::TIMEOUT, label, line);
        return &error;
      }
    }
    return nullptr;
  }

  unsigned long Timeout::_millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  }

}

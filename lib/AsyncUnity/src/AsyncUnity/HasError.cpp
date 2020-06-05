#include <memory>
#include "HasError.hpp"

namespace AsyncUnity {

  void HasError::setError(const Error::Code code, const char * label, const int line) {
    new(&error) Error(code, label, line);
    hasError = true;
  }

  void HasError::setError(const Error::Code code) {
    new(&error) Error(code);
    hasError = true;
  }

  void HasError::setError(const Error & e, const char * label, const int line) {
    new(&error) Error(e, label, line);
    hasError = true;
  }

  void HasError::setError(const Error & e) {
    new(&error) Error(e);
    hasError = true;
  }

  void HasError::setError() {
    new(&error) Error();
    hasError = true;
  }

  void HasError::unsetError() {
    hasError = false;
  }

}

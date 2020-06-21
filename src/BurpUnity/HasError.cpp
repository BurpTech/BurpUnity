#include <memory>
#include "HasError.hpp"

namespace BurpUnity {

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

  void HasError::setError(const Error & e, const char * label1, const char * label2, const int line) {
    new(&error) Error(e, label1, label2, line);
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

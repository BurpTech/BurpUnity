#include <memory>
#include "HasStaticError.hpp"

namespace BddUnity {

  Error HasStaticError::staticError;
  bool HasStaticError::hasStaticError = false;

  void HasStaticError::setStaticError(const Error::Code code, const char * label, const int line) {
    new(&staticError) Error(code, label, line);
    hasStaticError = true;
  }

  void HasStaticError::setStaticError(const Error::Code code) {
    new(&staticError) Error(code);
    hasStaticError = true;
  }

  void HasStaticError::setStaticError(const Error & e, const char * label, const int line) {
    new(&staticError) Error(e, label, line);
    hasStaticError = true;
  }

  void HasStaticError::setStaticError(const Error & e) {
    new(&staticError) Error(e);
    hasStaticError = true;
  }

  void HasStaticError::setStaticError() {
    new(&staticError) Error();
    hasStaticError = true;
  }

  void HasStaticError::unsetStaticError() {
    hasStaticError = false;
  }

}

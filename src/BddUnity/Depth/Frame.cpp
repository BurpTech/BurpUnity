#include "Frame.hpp"

namespace BddUnity {
  namespace Depth {

    Frame::Frame(const char * label, const long timeout) :
      label(label),
      timeout(timeout),
      beforeEach(CallbackType::NONE),
      afterEach(CallbackType::NONE)
    {}

    Frame::Frame(const Frame & frame) :
      label(frame.label),
      timeout(frame.timeout),
      beforeEach(frame.beforeEach),
      afterEach(frame.afterEach)
    {}

  }
}

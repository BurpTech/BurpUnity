#include "Frame.hpp"

namespace BddUnity {
  namespace Depth {

    Frame::Frame(const char * label, const long timeout) :
      label(label),
      timeout(timeout),
      before(CallbackType::NONE),
      after(CallbackType::NONE),
      beforeEach(CallbackType::NONE),
      afterEach(CallbackType::NONE)
    {}

    Frame::Frame(const Frame & frame) :
      label(frame.label),
      timeout(frame.timeout),
      before(frame.before),
      after(frame.after),
      beforeEach(frame.beforeEach),
      afterEach(frame.afterEach)
    {}

  }
}

#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace AsyncCallback {

      Params::Params(const char * label, const int line, const f_async cb, const long timeout) :
        label(label),
        line(line),
        cb(cb),
        timeout(timeout)
      {}

      Params::Params(const Params & params) :
        label(params.label),
        line(params.line),
        cb(params.cb),
        timeout(params.timeout)
      {}

    }
  }
}

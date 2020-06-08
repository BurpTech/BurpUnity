#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Callback {

      Params::Params(const char * label, const int line, const f_callback cb) :
        label(label),
        line(line),
        cb(cb)
      {}

      Params::Params(const Params & params) :
        label(params.label),
        line(params.line),
        cb(params.cb)
      {}

    }
  }
}

#pragma once

#include "Interface.hpp"

namespace BddUnity {
  namespace Context {

    class HasContext {

      protected:

        Context::Interface & _context;
        HasContext(Context::Interface & context);

    };

  }
}

#pragma once

#include "../Error.hpp"
#include "Interface.hpp"

namespace BddUnity {
  namespace Factory {

    template <class Type, class Params>
    class HasFactory {
      
      public:

        HasFactory(Factory::Interface<Type, Params> & factory) :
          _factory(factory)
        {}

        const Error * free() {
          const Error * e = _free();
          const Error * ret = _factory.free(this);
          if (!ret) ret = e;
          return ret;
        }

      protected:

        Factory::Interface<Type, Params> & _factory;

      private:

        virtual const Error * _free() = 0;

    };

  }
}

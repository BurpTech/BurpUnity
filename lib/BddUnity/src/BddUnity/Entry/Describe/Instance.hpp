#pragma once

#include "../../HasError.hpp"
#include "../../Factory/HasFactory.hpp"
#include "../Interface.hpp"
#include "../It/Params.hpp"
#include "../AsyncIt/Params.hpp"
#include "Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Describe {

      class Instance : public Interface, public HasError, public Factory::HasFactory<Interface, Params> {

        public:

          Instance(Factory::Interface<Interface, Params> & factory, const Params & params);

          void describe(const char * thing, const Params::f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);
          void describe(const char * thing, const int line, const Params::f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);
          void async(const char * should, const AsyncIt::Params::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);
          void async(const char * should, const int line, const AsyncIt::Params::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);
          void it(const char * should, const It::Params::f_testCallback it);
          void it(const char * should, const int line, const It::Params::f_testCallback it);

        private:

          const Params _params;
          Interface * _entries = nullptr;
          Interface * _entriesTail = nullptr;

          void _run(Depth::Interface & depth, Timeout & timeout, const f_done & done) override;
          void _append(Interface * entry);
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

#pragma once

#include <stdio.h>
#include "../Factory/Interface.hpp"
#include "../Depth/Interface.hpp"
#include "../Depth/Params.hpp"
#include "../Entry/Interface.hpp"
#include "../Entry/Pop/Params.hpp"
#include "../Entry/It/Params.hpp"
#include "../Entry/AsyncIt/Params.hpp"

namespace BddUnity {
  namespace Entry {
    namespace Describe {
      class Params;
    }
  }

  namespace Memory {

    class Interface {
      public:
        virtual Factory::Interface<Depth::Interface, Depth::Params> & getDepthFactory() = 0;
        virtual Factory::Interface<Entry::Interface, Entry::Describe::Params> & getDescribeFactory() = 0;
        virtual Factory::Interface<Entry::Interface, Entry::Pop::Params> & getPopFactory() = 0;
        virtual Factory::Interface<Entry::Interface, Entry::It::Params> & getItFactory() = 0;
        virtual Factory::Interface<Entry::Interface, Entry::AsyncIt::Params> & getAsyncItFactory() = 0;
        virtual int snprintParams(char * buffer, size_t size) = 0;
        virtual int snprintUsage(char * buffer, size_t size) = 0;
    };

  }
}

#pragma once

#include <stdio.h>
#include "Pool/Interface.hpp"
#include "../Depth/Interface.hpp"
#include "../Depth/Params.hpp"
#include "../Entry/Interface.hpp"
#include "../Entry/Describe/Params.hpp"
#include "../Entry/Pop/Params.hpp"
#include "../Entry/Test/Params.hpp"
#include "../Entry/It/Params.hpp"
#include "../Entry/AsyncIt/Params.hpp"
#include "../Entry/Callback/Params.hpp"
#include "../Entry/AsyncCallback/Params.hpp"
#include "../Entry/StackedCallback/Params.hpp"
#include "../Entry/StackedAsyncCallback/Params.hpp"
#include "../Entry/Describe/Setup.hpp"

namespace BddUnity {
  namespace Memory {

    class Interface {
      public:
        virtual Pool::Interface<Depth::Interface, Depth::Params> & getDepthPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::Describe::Params> & getDescribePool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::Pop::Params> & getPopPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::Test::Params> & getTestPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::It::Params> & getItPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::AsyncIt::Params> & getAsyncItPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::Callback::Params> & getCallbackPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & getAsyncCallbackPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::StackedCallback::Params> & getStackedCallbackPool() = 0;
        virtual Pool::Interface<Entry::Interface, Entry::StackedAsyncCallback::Params> & getStackedAsyncCallbackPool() = 0;
        virtual Pool::Interface<Entry::Describe::Setup, Entry::Describe::Setup> & getSetupPool() = 0;
        virtual int snprintParams(char * buffer, size_t size) = 0;
        virtual int snprintUsage(char * buffer, size_t size) = 0;
    };

  }
}

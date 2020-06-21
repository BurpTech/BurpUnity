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

namespace BurpUnity {
  namespace Memory {

    struct Params {
      size_t labelBufferSize;
      long defaultTimeout;
      bool safeMemPools;
      size_t maxModule;
      size_t maxDepth;
      size_t maxDescribe;
      size_t maxPop;
      size_t maxTest;
      size_t maxIt;
      size_t maxAsyncIt;
      size_t maxCallback;
      size_t maxAsyncCallback;
      size_t maxStackedCallback;
      size_t maxStackedAsyncCallback;
      size_t maxBeforeEach;
      size_t maxAsyncBeforeEach;
      size_t maxAfterEach;
      size_t maxAsyncAfterEach;
      size_t maxSetup;
      size_t maxLoop;
    };

    struct Usage {
      size_t maxModule;
      size_t maxDescribe;
      size_t maxPop;
      size_t maxTest;
      size_t maxIt;
      size_t maxAsyncIt;
      size_t maxCallback;
      size_t maxAsyncCallback;
      size_t maxStackedCallback;
      size_t maxStackedAsyncCallback;
      size_t maxSetup;
    };

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
        virtual const Params getParams() const = 0;
        virtual const Usage getUsage() const = 0;
    };

  }
}

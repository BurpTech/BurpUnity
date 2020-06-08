#pragma once

#include <stdio.h>
#include "Frame.hpp"
#include "../Error.hpp"
#include "../Memory/Pool/Interface.hpp"
#include "../Entry/Callback/Params.hpp"
#include "../Entry/AsyncCallback/Params.hpp"

namespace BddUnity {
  namespace Entry {
    class Interface;
    class List;
  }

  namespace Depth {

    class Interface {
      public:
        unsigned long highUsed = 0;
        virtual const Error * free() = 0;
        virtual const Error * push(const Frame & frame) = 0;
        virtual const Error * pop() = 0;
        virtual const char * getLabel(const char * field) = 0;
        virtual const char * getLabel(const char * field1, const char * field2) = 0;
        virtual const long getTimeout(const long timeout) = 0;
        virtual const Error * setBefore(const Entry::Callback::Params & params) = 0;
        virtual const Error * setBefore(const Entry::AsyncCallback::Params & params) = 0;
        virtual const Error * before(
          Entry::List & list,
          Memory::Pool::Interface<Entry::Interface, Entry::Callback::Params> & syncPool,
          Memory::Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & asyncPool
        ) = 0;
        virtual const Error * setAfter(const Entry::Callback::Params & params) = 0;
        virtual const Error * setAfter(const Entry::AsyncCallback::Params & params) = 0;
        virtual const Error * after(
          Entry::List & list,
          Memory::Pool::Interface<Entry::Interface, Entry::Callback::Params> & syncPool,
          Memory::Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & asyncPool
        ) = 0;
        virtual const Error * setBeforeEach(const Entry::Callback::Params & params) = 0;
        virtual const Error * setBeforeEach(const Entry::AsyncCallback::Params & params) = 0;
        virtual const Error * beforeEach(
          Entry::List & list,
          Memory::Pool::Interface<Entry::Interface, Entry::Callback::Params> & syncPool,
          Memory::Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & asyncPool
        ) = 0;
        virtual const Error * setAfterEach(const Entry::Callback::Params & params) = 0;
        virtual const Error * setAfterEach(const Entry::AsyncCallback::Params & params) = 0;
        virtual const Error * afterEach(
          Entry::List & list,
          Memory::Pool::Interface<Entry::Interface, Entry::Callback::Params> & syncPool,
          Memory::Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & asyncPool
        ) = 0;
        virtual const size_t getMaxDepth() = 0;
    };

  }
}

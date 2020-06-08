#pragma once

#include <stdio.h>
#include "Frame.hpp"
#include "../Error.hpp"
#include "../Memory/Pool/Interface.hpp"
#include "../Entry/Callback/Params.hpp"
#include "../Entry/AsyncCallback/Params.hpp"
#include "../Entry/Describe/Loop.hpp"

#define BDD_UNITY_DEPTH_CALLBACK(NAME, SET_NAME)\
  virtual const Error * SET_NAME(const Entry::Callback::Params & params) = 0;\
  virtual const Error * SET_NAME(const Entry::AsyncCallback::Params & params) = 0;\
  virtual const Error * NAME(\
    Entry::List & list,\
    Memory::Pool::Interface<Entry::Interface, Entry::Callback::Params> & syncPool,\
    Memory::Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & asyncPool\
  ) = 0

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
        BDD_UNITY_DEPTH_CALLBACK(before, setBefore);
        BDD_UNITY_DEPTH_CALLBACK(after, setAfter);
        BDD_UNITY_DEPTH_CALLBACK(beforeEach, setBeforeEach);
        BDD_UNITY_DEPTH_CALLBACK(afterEach, setAfterEach);
        virtual const Error * setLoop(const Entry::Describe::Loop & loop) = 0;
        virtual void loop() = 0;
        virtual const size_t getMaxDepth() = 0;
    };

  }
}

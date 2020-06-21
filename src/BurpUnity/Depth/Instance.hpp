#pragma once

#include <cstddef>
#include <memory>
#include <stdio.h>
#include "Frame.hpp"
#include "Interface.hpp"
#include "Params.hpp"
#include "../Entry/List.hpp"
#include "../Entry/StackedCallback/Params.hpp"
#include "../Entry/StackedAsyncCallback/Params.hpp"
#include "../Memory/Pool/HasPool.hpp"
#include "../Memory/Stack/Instance.hpp"
#include "../Memory/Stack/Interface.hpp"

#define BURP_UNITY_DEPTH_SYNC_SET(NAME, SET_NAME, ERROR_CODE, STACK)\
  const Error * SET_NAME(const Entry::StackedCallback::Params & params) override {\
    Frame & frame = *(_frameStack.current());\
    if (frame.NAME != Frame::CallbackType::NONE) {\
      setError(Error::Code::ERROR_CODE);\
      return &error;\
    }\
    frame.NAME = Frame::CallbackType::SYNC;\
    return STACK.push(params);\
  }
#define BURP_UNITY_DEPTH_ASYNC_SET(NAME, SET_NAME, ERROR_CODE, STACK)\
  const Error * SET_NAME(const Entry::StackedAsyncCallback::Params & params) override {\
    Frame & frame = *(_frameStack.current());\
    if (frame.NAME != Frame::CallbackType::NONE) {\
      setError(Error::Code::ERROR_CODE);\
      return &error;\
    }\
    frame.NAME = Frame::CallbackType::ASYNC;\
    return STACK.push(params);\
  }
#define BURP_UNITY_DEPTH_CALLBACK_IMPL(NAME, SET_NAME, ERROR_CODE, SYNC_STACK, ASYNC_STACK, APPEND)\
  BURP_UNITY_DEPTH_SYNC_SET(NAME, SET_NAME, ERROR_CODE, SYNC_STACK)\
  BURP_UNITY_DEPTH_ASYNC_SET(NAME, SET_NAME, ERROR_CODE, ASYNC_STACK)\
  const Error * NAME(\
    Entry::List & list,\
    Memory::Pool::Interface<Entry::Interface, Entry::StackedCallback::Params> & syncPool,\
    Memory::Pool::Interface<Entry::Interface, Entry::StackedAsyncCallback::Params> & asyncPool\
  ) override {\
    size_t syncIndex = 0;\
    size_t asyncIndex = 0;\
    return _frameStack.forEach([&](const Frame & frame) {\
      return _createEntry(\
        frame.NAME,\
        list,\
        APPEND,\
        syncPool,\
        asyncPool,\
        SYNC_STACK,\
        ASYNC_STACK,\
        syncIndex,\
        asyncIndex\
      );\
    });\
  }

namespace BurpUnity {
  namespace Depth {

    template <
      size_t maxDepth,
      size_t labelBufferSize,
      long defaultTimeout,
      size_t maxBeforeEach,
      size_t maxAsyncBeforeEach,
      size_t maxAfterEach,
      size_t maxAsyncAfterEach,
      size_t maxLoop,
      bool safe
    >
    class Instance : public Interface, public Memory::Pool::HasPool<Interface, Params> {
      
      public:

        Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params) :
          Memory::Pool::HasPool<Interface, Params>(pool)
        {}

        const Error * free() override {
          return Memory::Pool::HasPool<Interface, Params>::free(this);
        }

        const Error * push(const Frame & frame) override {
          return _frameStack.push(frame);
        }

        const Error * pop() override {
          const Error * ret = nullptr;
          const Error * e;
          const Frame & frame = *(_frameStack.current());
          e = _popEntryParams(frame.beforeEach, _beforeEachStack, _asyncBeforeEachStack);
          if (e) ret = e;
          e = _popEntryParams(frame.afterEach, _afterEachStack, _asyncAfterEachStack);
          if (e) ret = e;
          e = _popLoop(frame.hasLoop);
          if (e) ret = e;
          e = _frameStack.pop();
          if (e) ret = e;
          return ret;
        }

        const char * getLabel(const char * field) override {
          _resetLabel();
          _concatenateLabel(field);
          return _currentLabel;
        }

        const char * getLabel(const char * field1, const char * field2) override {
          _resetLabel();
          _concatenateLabel(field1);
          _concatenateLabel(field2);
          return _currentLabel;
        }

        BURP_UNITY_DEPTH_CALLBACK_IMPL(beforeEach, setBeforeEach, BEFORE_EACH_SET, _beforeEachStack, _asyncBeforeEachStack, true)
        BURP_UNITY_DEPTH_CALLBACK_IMPL(afterEach, setAfterEach, AFTER_EACH_SET, _afterEachStack, _asyncAfterEachStack, false)

        const Error * setLoop(const Entry::Describe::Loop & loop) override {
          Frame & frame = *(_frameStack.current());
          if (frame.hasLoop) {
            setError(Error::Code::HAS_LOOP);
            return &error;
          }
          frame.hasLoop = true;
          return _loopStack.push(loop);
        }

        void loop() override {
          _loopStack.forEach([&](const Entry::Describe::Loop & loop) {
            loop.cb();
            return nullptr;
          });
        }

        const long getTimeout(const long timeout) override {
          if (0 != timeout) {
            // timeout has been overriden
            return timeout;
          }
          long ret = defaultTimeout;
          _frameStack.forEach([&](const Frame & frame) {
            // only apply next timeout if it is an override
            const long t = frame.timeout;
            if (0 != t) {
              ret = t;
            }
            return nullptr;
          });
          return ret;
        }

        const Usage getUsage() const override {
          return {
            _frameStack.highUsed,
            _beforeEachStack.highUsed,
            _asyncBeforeEachStack.highUsed,
            _afterEachStack.highUsed,
            _asyncAfterEachStack.highUsed,
            _loopStack.highUsed
          };
        }

      private:
        
        Memory::Stack::Instance<
          Frame,
          Frame,
          Frame,
          maxDepth,
          safe
        > _frameStack;

        Memory::Stack::Instance<
          Entry::StackedCallback::Params,
          Entry::StackedCallback::Params,
          Entry::StackedCallback::Params,
          maxBeforeEach,
          safe
        > _beforeEachStack;

        Memory::Stack::Instance<
          Entry::StackedAsyncCallback::Params,
          Entry::StackedAsyncCallback::Params,
          Entry::StackedAsyncCallback::Params,
          maxAsyncBeforeEach,
          safe
        > _asyncBeforeEachStack;

        Memory::Stack::Instance<
          Entry::StackedCallback::Params,
          Entry::StackedCallback::Params,
          Entry::StackedCallback::Params,
          maxAfterEach,
          safe
        > _afterEachStack;

        Memory::Stack::Instance<
          Entry::StackedAsyncCallback::Params,
          Entry::StackedAsyncCallback::Params,
          Entry::StackedAsyncCallback::Params,
          maxAsyncAfterEach,
          safe
        > _asyncAfterEachStack;

        Memory::Stack::Instance<
          Entry::Describe::Loop,
          Entry::Describe::Loop,
          Entry::Describe::Loop,
          maxLoop,
          safe
        > _loopStack;

        // we use 2 buffers to make concatenation simpler
        char _label1[labelBufferSize];
        char _label2[labelBufferSize];
        char * _currentLabel;

        void _resetLabel() {
          _currentLabel = _label1;
          _currentLabel[0] = 0;

          _frameStack.forEach([&](const Frame & frame) {
            _concatenateLabel(frame.label);
            return nullptr;
          });
        }

        void  _concatenateLabel(const char * field) {
          char * destination = _currentLabel == _label1 ? _label2 : _label1;
          snprintf(destination, labelBufferSize, "%s[%s]", _currentLabel, field);
          _currentLabel = destination;
        }

        const Error * _free() override {
          return nullptr;
        }

        const Error * _popLoop(bool hasLoop) {
          if (hasLoop) {
            return _loopStack.pop();
          }
          return nullptr;
        }

        static const Error * _popEntryParams(
          const Frame::CallbackType type,
          Memory::Stack::Interface<Entry::StackedCallback::Params, Entry::StackedCallback::Params> & syncStack,
          Memory::Stack::Interface<Entry::StackedAsyncCallback::Params, Entry::StackedAsyncCallback::Params> & asyncStack
        ) {
          switch (type) {
            case Frame::CallbackType::NONE:
              // do nothing
              return nullptr;
            case Frame::CallbackType::SYNC:
              return syncStack.pop();
            case Frame::CallbackType::ASYNC:
              return asyncStack.pop();
          }
          return nullptr;
        }

        static const Error * _createEntry(
          const Frame::CallbackType type,
          Entry::List & list,
          const bool append,
          Memory::Pool::Interface<Entry::Interface, Entry::StackedCallback::Params> & syncPool,
          Memory::Pool::Interface<Entry::Interface, Entry::StackedAsyncCallback::Params> & asyncPool,
          Memory::Stack::Interface<Entry::StackedCallback::Params, Entry::StackedCallback::Params> & syncStack,
          Memory::Stack::Interface<Entry::StackedAsyncCallback::Params, Entry::StackedAsyncCallback::Params> & asyncStack,
          size_t & syncIndex,
          size_t & asyncIndex
        ) {
          Entry::Interface * entry = nullptr;
          switch (type) {
            case Frame::CallbackType::NONE:
              // do nothing
              return nullptr;
            case Frame::CallbackType::SYNC:
              {
                const Entry::StackedCallback::Params * params = syncStack.get(syncIndex++);
                entry = syncPool.create(*params);
                if (!entry) {
                  return &(syncPool.error);
                }
              }
              break;
            case Frame::CallbackType::ASYNC:
              {
                entry = asyncPool.create(*(asyncStack.get(asyncIndex++)));
                if (!entry) {
                  return &(asyncPool.error);
                }
              }
              break;
          }
          if (append) {
            list.append(entry);
          } else {
            list.prepend(entry);
          }
          return nullptr;
        }
    };

  }
}

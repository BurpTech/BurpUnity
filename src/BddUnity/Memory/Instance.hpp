#pragma once

#include "Pool/Instance.hpp"
#include "../Depth/Instance.hpp"
#include "Interface.hpp"
#include "../Entry/Describe/Instance.hpp"
#include "../Entry/Pop/Instance.hpp"
#include "../Entry/Test/Instance.hpp"
#include "../Entry/It/Instance.hpp"
#include "../Entry/AsyncIt/Instance.hpp"
#include "../Entry/Callback/Instance.hpp"
#include "../Entry/AsyncCallback/Instance.hpp"
#include "../Entry/StackedCallback/Instance.hpp"
#include "../Entry/StackedAsyncCallback/Instance.hpp"
#include <cstddef>

namespace BddUnity {
  namespace Memory {

    template <
      size_t labelBufferSize,
      long defaultTimeout,
      bool safeMemPools,
      size_t maxModule,
      size_t maxDepth,
      size_t maxDescribe,
      size_t maxPop,
      size_t maxTest,
      size_t maxIt,
      size_t maxAsyncIt,
      size_t maxCallback,
      size_t maxAsyncCallback,
      size_t maxStackedCallback,
      size_t maxStackedAsyncCallback,
      size_t maxBeforeEach,
      size_t maxAsyncBeforeEach,
      size_t maxAfterEach,
      size_t maxAsyncAfterEach,
      size_t maxSetup,
      size_t maxLoop
    >
    class Instance : public Interface {

      public:

        Pool::Interface<Depth::Interface, Depth::Params> & getDepthPool() override {
          return _depthPool;
        }

        Pool::Interface<Entry::Interface, Entry::Describe::Params> & getDescribePool() override {
          return _describePool;
        }

        Pool::Interface<Entry::Interface, Entry::Pop::Params> & getPopPool() override {
          return _popPool;
        }

        Pool::Interface<Entry::Interface, Entry::Test::Params> & getTestPool() override {
          return _testPool;
        }

        Pool::Interface<Entry::Interface, Entry::It::Params> & getItPool() override {
          return _itPool;
        }

        Pool::Interface<Entry::Interface, Entry::AsyncIt::Params> & getAsyncItPool() override {
          return _asyncItPool;
        }

        Pool::Interface<Entry::Interface, Entry::Callback::Params> & getCallbackPool() override {
          return _callbackPool;
        }

        Pool::Interface<Entry::Interface, Entry::AsyncCallback::Params> & getAsyncCallbackPool() override {
          return _asyncCallbackPool;
        }

        Pool::Interface<Entry::Interface, Entry::StackedCallback::Params> & getStackedCallbackPool() override {
          return _stackedCallbackPool;
        }

        Pool::Interface<Entry::Interface, Entry::StackedAsyncCallback::Params> & getStackedAsyncCallbackPool() override {
          return _stackedAsyncCallbackPool;
        }

        Pool::Interface<Entry::Describe::Setup, Entry::Describe::Setup> & getSetupPool() override {
          return _setupPool;
        }

        const Params getParams() const override {
          return {
            labelBufferSize,
            defaultTimeout,
            safeMemPools,
            maxModule,
            maxDepth,
            maxDescribe,
            maxPop,
            maxTest,
            maxIt,
            maxAsyncIt,
            maxCallback,
            maxAsyncCallback,
            maxStackedCallback,
            maxStackedAsyncCallback,
            maxBeforeEach,
            maxAsyncBeforeEach,
            maxAfterEach,
            maxAsyncAfterEach,
            maxSetup,
            maxLoop
          };
        }

        const Usage getUsage() const override {
          return {
            _depthPool.highUsed,
            _describePool.highUsed,
            _popPool.highUsed,
            _testPool.highUsed,
            _itPool.highUsed,
            _asyncItPool.highUsed,
            _callbackPool.highUsed,
            _asyncCallbackPool.highUsed,
            _stackedCallbackPool.highUsed,
            _stackedAsyncCallbackPool.highUsed,
            _setupPool.highUsed
          };
        }

      private:

        Pool::Instance<
          Depth::Interface,
          Depth::Instance<
            maxDepth,
            labelBufferSize,
            defaultTimeout,
            maxBeforeEach,
            maxAsyncBeforeEach,
            maxAfterEach,
            maxAsyncAfterEach,
            maxLoop,
            safeMemPools
          >,
          Depth::Params,
          maxModule,
          safeMemPools
        > _depthPool;
        Pool::Instance<
          Entry::Interface,
          Entry::Describe::Instance,
          Entry::Describe::Params,
          maxDescribe,
          safeMemPools
        > _describePool;
        Pool::Instance<
          Entry::Interface,
          Entry::Pop::Instance,
          Entry::Pop::Params,
          maxPop,
          safeMemPools
        > _popPool;
        Pool::Instance<
          Entry::Interface,
          Entry::Test::Instance,
          Entry::Test::Params,
          maxTest,
          safeMemPools
        > _testPool;
        Pool::Instance<
          Entry::Interface,
          Entry::It::Instance,
          Entry::It::Params,
          maxIt,
          safeMemPools
        > _itPool;
        Pool::Instance<
          Entry::Interface,
          Entry::AsyncIt::Instance,
          Entry::AsyncIt::Params,
          maxAsyncIt,
          safeMemPools
        > _asyncItPool;
        Pool::Instance<
          Entry::Interface,
          Entry::Callback::Instance,
          Entry::Callback::Params,
          maxCallback,
          safeMemPools
        > _callbackPool;
        Pool::Instance<
          Entry::Interface,
          Entry::AsyncCallback::Instance,
          Entry::AsyncCallback::Params,
          maxAsyncCallback,
          safeMemPools
        > _asyncCallbackPool;
        Pool::Instance<
          Entry::Interface,
          Entry::StackedCallback::Instance,
          Entry::StackedCallback::Params,
          maxCallback,
          safeMemPools
        > _stackedCallbackPool;
        Pool::Instance<
          Entry::Interface,
          Entry::StackedAsyncCallback::Instance,
          Entry::StackedAsyncCallback::Params,
          maxAsyncCallback,
          safeMemPools
        > _stackedAsyncCallbackPool;
        Pool::Instance<
          Entry::Describe::Setup,
          Entry::Describe::Setup,
          Entry::Describe::Setup,
          maxSetup,
          safeMemPools
        > _setupPool;

    };

  }
}

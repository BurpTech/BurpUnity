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

        int snprintParams(char * buffer, size_t size) override {

          const char * format = 
            "----------------------------\n"
            "BddUnity: memory parameters:\n"
            "----------------------------\n"
            "safeMemPools: %d\n"
            "maxModule: %d\n"
            "maxDepth: %d\n"
            "labelBufferSize: %d\n"
            "defaultTimeout: %d\n"
            "maxDescribe: %d\n"
            "maxPop: %d\n"
            "maxTest: %d\n"
            "maxIt: %d\n"
            "maxAsyncIt: %d\n"
            "maxCallback: %d\n"
            "maxAsyncCallback: %d\n"
            "maxStackedCallback: %d\n"
            "maxStackedAsyncCallback: %d\n"
            "maxBeforeEach: %d\n"
            "maxAsyncBeforeEach: %d\n"
            "maxAfterEach: %d\n"
            "maxAsyncAfterEach: %d\n"
            "maxSetup: %d\n"
            "maxLoop: %d\n";

          return snprintf(buffer, size, format,
            safeMemPools,
            maxModule,
            maxDepth,
            labelBufferSize,
            defaultTimeout,
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
            maxLoop);

        }

        int snprintUsage(char * buffer, size_t size) override {

          const char * format = 
            "-----------------------\n"
            "BddUnity: memory usage:\n"
            "-----------------------\n"
            "maximum modules allocated (BDD_UNITY_MAX_MODULE): %lu (%d)\n"
            "maximum describes allocated (BDD_UNITY_MAX_DESCRIBE): %lu (%d)\n"
            "maximum pops allocated (BDD_UNITY_MAX_POP): %lu (%d)\n"
            "maximum tests allocated (BDD_UNITY_MAX_TEST): %lu (%d)\n"
            "maximum its allocated (BDD_UNITY_MAX_IT): %lu (%d)\n"
            "maximum async its allocated (BDD_UNITY_MAX_ASYNC_IT): %lu (%d)\n"
            "maximum callbacks allocated (BDD_UNITY_MAX_CALLBACK): %lu (%d)\n"
            "maximum async callbacks allocated (BDD_UNITY_MAX_ASYNC_CALLBACK): %lu (%d)\n"
            "maximum stacked callbacks allocated (BDD_UNITY_MAX_STACKED_CALLBACK): %lu (%d)\n"
            "maximum stacked async callbacks allocated (BDD_UNITY_MAX_STACKED_ASYNC_CALLBACK): %lu (%d)\n"
            "maximum setups allocated (BDD_UNITY_MAX_SETUP): %lu (%d)\n";

          return snprintf(buffer, size, format,
            _depthPool.highUsed,
            maxModule,
            _describePool.highUsed,
            maxDescribe,
            _popPool.highUsed,
            maxPop,
            _testPool.highUsed,
            maxTest,
            _itPool.highUsed,
            maxIt,
            _asyncItPool.highUsed,
            maxAsyncIt,
            _callbackPool.highUsed,
            maxCallback,
            _asyncCallbackPool.highUsed,
            maxAsyncCallback,
            _stackedCallbackPool.highUsed,
            maxStackedCallback,
            _stackedAsyncCallbackPool.highUsed,
            maxStackedAsyncCallback,
            _setupPool.highUsed,
            maxSetup);

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

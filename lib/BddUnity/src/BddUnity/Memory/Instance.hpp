#pragma once

#include "../Factory/Instance.hpp"
#include "../Depth/Instance.hpp"
#include "Interface.hpp"
#include "../Entry/Describe/Instance.hpp"
#include "../Entry/Pop/Instance.hpp"
#include "../Entry/It/Instance.hpp"
#include "../Entry/AsyncIt/Instance.hpp"

namespace BddUnity {
  namespace Memory {

    template <
      size_t labelBufferSize,
      long defaultTimeout,
      bool safeMemPools,
      size_t maxModules,
      size_t maxDepth,
      size_t maxDescribes,
      size_t maxPops,
      size_t maxIts,
      size_t maxAsyncIts>
    class Instance : public Interface {

      public:

        Factory::Interface<Depth::Interface, Depth::Params> & getDepthFactory() override {
          return _depthFactory;
        }

        Factory::Interface<Entry::Interface, Entry::Describe::Params> & getDescribeFactory() override {
          return _describeFactory;
        }

        Factory::Interface<Entry::Interface, Entry::Pop::Params> & getPopFactory() override {
          return _popFactory;
        }

        Factory::Interface<Entry::Interface, Entry::It::Params> & getItFactory() override {
          return _itFactory;
        }

        Factory::Interface<Entry::Interface, Entry::AsyncIt::Params> & getAsyncItFactory() override {
          return _asyncItFactory;
        }

        int snprintParams(char * buffer, size_t size) override {

          const char * format = 
            "----------------------------\n"
            "BddUnity: memory parameters:\n"
            "----------------------------\n"
            "safeMemPools: %d\n"
            "maxModules: %d\n"
            "maxDepth: %d\n"
            "labelBufferSize: %d\n"
            "defaultTimeout: %d\n"
            "maxDescribes: %d\n"
            "maxPops: %d\n"
            "maxIts: %d\n"
            "maxAsyncIts: %d\n";

          return snprintf(buffer, size, format,
            safeMemPools,
            maxModules,
            maxDepth,
            labelBufferSize,
            defaultTimeout,
            maxDescribes,
            maxPops,
            maxIts,
            maxAsyncIts);

        }

        int snprintUsage(char * buffer, size_t size) override {

          const char * format = 
            "-----------------------\n"
            "BddUnity: memory usage:\n"
            "-----------------------\n"
            "maximum modules allocated (BDD_UNITY_MAX_MODULES): %lu (%d)\n"
            "maximum describes allocated (BDD_UNITY_MAX_DESCRIBES): %lu (%d)\n"
            "maximum pops allocated (BDD_UNITY_MAX_POPS): %lu (%d)\n"
            "maximum its allocated (BDD_UNITY_MAX_ITS): %lu (%d)\n"
            "maximum async its allocated (BDD_UNITY_MAX_ASYNC_ITS): %lu (%d)\n";

          return snprintf(buffer, size, format,
            _depthFactory.highUsed,
            maxModules,
            _describeFactory.highUsed,
            maxDescribes,
            _popFactory.highUsed,
            maxPops,
            _itFactory.highUsed,
            maxIts,
            _asyncItFactory.highUsed,
            maxAsyncIts);

        }

      private:

        Factory::Instance<
          Depth::Interface,
          Depth::Instance<maxDepth, labelBufferSize, defaultTimeout>,
          Depth::Params,
          maxModules,
          safeMemPools
        > _depthFactory;
        Factory::Instance<
          Entry::Interface,
          Entry::Describe::Instance,
          Entry::Describe::Params,
          maxDescribes,
          safeMemPools
        > _describeFactory;
        Factory::Instance<
          Entry::Interface,
          Entry::Pop::Instance,
          Entry::Pop::Params,
          maxPops,
          safeMemPools
        > _popFactory;
        Factory::Instance<
          Entry::Interface,
          Entry::It::Instance,
          Entry::It::Params,
          maxIts,
          safeMemPools
        > _itFactory;
        Factory::Instance<
          Entry::Interface,
          Entry::AsyncIt::Instance,
          Entry::AsyncIt::Params,
          maxAsyncIts,
          safeMemPools
        > _asyncItFactory;

    };

  }
}

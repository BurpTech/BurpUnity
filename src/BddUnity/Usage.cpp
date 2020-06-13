#include <stdio.h>
#include "Usage.hpp"

#ifndef BDD_UNITY_SIZE_T_FORMAT
#define BDD_UNITY_SIZE_T_FORMAT "%lu"
#endif

#define PRINT_FIELD(FORMAT, OBJECT, NAME) printf(#NAME ": " FORMAT "\n", OBJECT.NAME)
#define PRINT_FIELD_DEFINE(DEFINE, FORMAT, OBJECT, NAME) printf("#define " #DEFINE " " FORMAT "\n", OBJECT.NAME)

namespace BddUnity {
  namespace Usage {

    void printParams(const Memory::Interface & memory) {
      Memory::Params params = memory.getParams();
      printf("----------------------------\n");
      printf("BddUnity::Memory parameters:\n");
      printf("----------------------------\n");
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, labelBufferSize);
      PRINT_FIELD("%ld", params, defaultTimeout);
      PRINT_FIELD("%d", params, safeMemPools);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxModule);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxDepth);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxDescribe);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxPop);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxTest);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxIt);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxAsyncIt);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxAsyncCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxStackedCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxStackedAsyncCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxBeforeEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxAsyncBeforeEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxAfterEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxAsyncAfterEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxSetup);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, params, maxLoop);
      printf("----------------------------\n");
    }

    void printUsage(const Memory::Interface & memory, const Runnable & runnable) {
      printMemoryUsage(memory);
      printDepthUsage(runnable);
    }

    void printMemoryUsage(const Memory::Interface & memory) {
      BddUnity::Memory::Usage usage = memory.getUsage();
      printf("-----------------------\n");
      printf("BddUnity::Memory::Usage:\n");
      printf("-----------------------\n");
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxModule);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxDescribe);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxPop);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxTest);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxIt);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncIt);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxStackedCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxStackedAsyncCallback);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxSetup);
      printf("-----------------------\n");
    }

    void printDepthUsage(const Runnable & runnable) {
      BddUnity::Depth::Usage usage = runnable.getUsage();
      printf("-----------------------\n");
      printf("BddUnity::Depth::Usage:\n");
      printf("-----------------------\n");
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxDepth);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxBeforeEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncBeforeEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxAfterEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncAfterEach);
      PRINT_FIELD(BDD_UNITY_SIZE_T_FORMAT, usage, maxLoop);
      printf("-----------------------\n");
    }

    void printUsageDefines(const Memory::Interface & memory, const Runnable & runnable) {
      printMemoryUsageDefines(memory);
      printDepthUsageDefines(runnable);
    }

    void printMemoryUsageDefines(const Memory::Interface & memory) {
      BddUnity::Memory::Usage usage = memory.getUsage();
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_MODULE, BDD_UNITY_SIZE_T_FORMAT, usage, maxModule);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_DESCRIBE, BDD_UNITY_SIZE_T_FORMAT, usage, maxDescribe);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_POP, BDD_UNITY_SIZE_T_FORMAT, usage, maxPop);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_TEST, BDD_UNITY_SIZE_T_FORMAT, usage, maxTest);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_IT, BDD_UNITY_SIZE_T_FORMAT, usage, maxIt);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_ASYNC_IT, BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncIt);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_CALLBACK, BDD_UNITY_SIZE_T_FORMAT, usage, maxCallback);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_ASYNC_CALLBACK, BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncCallback);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_STACKED_CALLBACK, BDD_UNITY_SIZE_T_FORMAT, usage, maxStackedCallback);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_STACKED_ASYNC_CALLBACK, BDD_UNITY_SIZE_T_FORMAT, usage, maxStackedAsyncCallback);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_SETUP, BDD_UNITY_SIZE_T_FORMAT, usage, maxSetup);
    }

    void printDepthUsageDefines(const Runnable & runnable) {
      BddUnity::Depth::Usage usage = runnable.getUsage();
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_DEPTH, BDD_UNITY_SIZE_T_FORMAT, usage, maxDepth);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_BEFORE_EACH, BDD_UNITY_SIZE_T_FORMAT, usage, maxBeforeEach);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_ASYNC_BEFORE_EACH, BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncBeforeEach);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_AFTER_EACH, BDD_UNITY_SIZE_T_FORMAT, usage, maxAfterEach);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_ASYNC_AFTER_EACH, BDD_UNITY_SIZE_T_FORMAT, usage, maxAsyncAfterEach);
      PRINT_FIELD_DEFINE(BDD_UNITY_MAX_LOOP, BDD_UNITY_SIZE_T_FORMAT, usage, maxLoop);
    }

  }
}

#include <stdio.h>
#include "Usage.hpp"

#ifndef BURP_SIZE_T_FORMAT
#define BURP_SIZE_T_FORMAT "%lu"
#endif

#define PRINT_FIELD(FORMAT, OBJECT, NAME) printf(#NAME ": " FORMAT "\n", OBJECT.NAME)
#define PRINT_FIELD_DEFINE(DEFINE, FORMAT, OBJECT, NAME) printf("#define " #DEFINE " " FORMAT "\n", OBJECT.NAME)

namespace BurpUnity {
  namespace Usage {

    void printParams(const Memory::Interface & memory) {
      Memory::Params params = memory.getParams();
      printf("----------------------------\n");
      printf("BurpUnity::Memory parameters:\n");
      printf("----------------------------\n");
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, labelBufferSize);
      PRINT_FIELD("%ld", params, defaultTimeout);
      PRINT_FIELD("%d", params, safeMemPools);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxModule);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxDepth);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxDescribe);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxPop);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxTest);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxIt);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxAsyncIt);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxAsyncCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxStackedCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxStackedAsyncCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxBeforeEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxAsyncBeforeEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxAfterEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxAsyncAfterEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxSetup);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, params, maxLoop);
      printf("----------------------------\n");
    }

    void printUsage(const Memory::Interface & memory, const Runnable & runnable) {
      printMemoryUsage(memory);
      printDepthUsage(runnable);
    }

    void printMemoryUsage(const Memory::Interface & memory) {
      BurpUnity::Memory::Usage usage = memory.getUsage();
      printf("-----------------------\n");
      printf("BurpUnity::Memory::Usage:\n");
      printf("-----------------------\n");
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxModule);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxDescribe);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxPop);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxTest);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxIt);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxAsyncIt);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxAsyncCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxStackedCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxStackedAsyncCallback);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxSetup);
      printf("-----------------------\n");
    }

    void printDepthUsage(const Runnable & runnable) {
      BurpUnity::Depth::Usage usage = runnable.getUsage();
      printf("-----------------------\n");
      printf("BurpUnity::Depth::Usage:\n");
      printf("-----------------------\n");
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxDepth);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxBeforeEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxAsyncBeforeEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxAfterEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxAsyncAfterEach);
      PRINT_FIELD(BURP_SIZE_T_FORMAT, usage, maxLoop);
      printf("-----------------------\n");
    }

    void printUsageDefines(const Memory::Interface & memory, const Runnable & runnable) {
      printMemoryUsageDefines(memory);
      printDepthUsageDefines(runnable);
    }

    void printMemoryUsageDefines(const Memory::Interface & memory) {
      BurpUnity::Memory::Usage usage = memory.getUsage();
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_MODULE, BURP_SIZE_T_FORMAT, usage, maxModule);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_DESCRIBE, BURP_SIZE_T_FORMAT, usage, maxDescribe);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_POP, BURP_SIZE_T_FORMAT, usage, maxPop);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_TEST, BURP_SIZE_T_FORMAT, usage, maxTest);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_IT, BURP_SIZE_T_FORMAT, usage, maxIt);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_ASYNC_IT, BURP_SIZE_T_FORMAT, usage, maxAsyncIt);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_CALLBACK, BURP_SIZE_T_FORMAT, usage, maxCallback);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_ASYNC_CALLBACK, BURP_SIZE_T_FORMAT, usage, maxAsyncCallback);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_STACKED_CALLBACK, BURP_SIZE_T_FORMAT, usage, maxStackedCallback);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_STACKED_ASYNC_CALLBACK, BURP_SIZE_T_FORMAT, usage, maxStackedAsyncCallback);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_SETUP, BURP_SIZE_T_FORMAT, usage, maxSetup);
    }

    void printDepthUsageDefines(const Runnable & runnable) {
      BurpUnity::Depth::Usage usage = runnable.getUsage();
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_DEPTH, BURP_SIZE_T_FORMAT, usage, maxDepth);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_BEFORE_EACH, BURP_SIZE_T_FORMAT, usage, maxBeforeEach);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_ASYNC_BEFORE_EACH, BURP_SIZE_T_FORMAT, usage, maxAsyncBeforeEach);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_AFTER_EACH, BURP_SIZE_T_FORMAT, usage, maxAfterEach);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_ASYNC_AFTER_EACH, BURP_SIZE_T_FORMAT, usage, maxAsyncAfterEach);
      PRINT_FIELD_DEFINE(BURP_UNITY_MAX_LOOP, BURP_SIZE_T_FORMAT, usage, maxLoop);
    }

  }
}

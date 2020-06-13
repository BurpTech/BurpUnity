#include <stdio.h>
#include "Usage.hpp"

#ifndef BDD_UNITY_SIZE_T_FORMAT
#define BDD_UNITY_SIZE_T_FORMAT "%lu"
#endif

#define PRINT_FIELD(FORMAT, OBJECT, NAME) printf(#NAME ": " FORMAT "\n", OBJECT.NAME)

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

    void printUsage(const Memory::Interface & memory, const Runnable & runnable) {
      printMemoryUsage(memory);
      printDepthUsage(runnable);
    }
  }
}

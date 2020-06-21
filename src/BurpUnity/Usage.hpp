#pragma once

#include "Memory/Interface.hpp"
#include "Runnable.hpp"

namespace BurpUnity {
  namespace Usage {

    void printParams(const Memory::Interface & memory);

    void printUsage(const Memory::Interface & memory, const Runnable & runnable);
    void printMemoryUsage(const Memory::Interface & memory);
    void printDepthUsage(const Runnable & runnable);

    void printUsageDefines(const Memory::Interface & memory, const Runnable & runnable);
    void printMemoryUsageDefines(const Memory::Interface & memory);
    void printDepthUsageDefines(const Runnable & runnable);

  }
}

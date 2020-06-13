#pragma once

#include "Memory/Interface.hpp"
#include "Runnable.hpp"

namespace BddUnity {
  namespace Usage {

    void printParams(const Memory::Interface & memory);
    void printMemoryUsage(const Memory::Interface & memory);
    void printDepthUsage(const Runnable & runnable);
    void printUsage(const Memory::Interface & memory, const Runnable & runnable);

  }
}

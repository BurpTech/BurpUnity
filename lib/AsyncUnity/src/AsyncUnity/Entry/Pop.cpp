#include "./Pop.hpp"
#include "../Globals.hpp"

namespace AsyncUnity {
  namespace Entry {

        const Error * Pop::error = nullptr;

        Pop * Pop::create() {
          void * address = Globals::popMemPool.alloc();
          if (address) {
            return new(address) Pop;
          }
          error = Globals::popMemPool.error;
          return nullptr;
        }

        const Error * Pop::free() {
          return Globals::popMemPool.free(this);
        }

        void Pop::run(f_done done) {
          Globals::timeout.timeout = Timeout::NO_TIMEOUT;
          done(Globals::depth.pop());
          return;
        }

  }
}

#include "../Globals.hpp"
#include "Pop.hpp"

namespace AsyncUnity {
  namespace Entry {

        Pop * Pop::create() {
          void * address = Globals::popMemPool.alloc();
          if (address) {
            return new(address) Pop;
          }
          setStaticError(Globals::popMemPool.error);
          return nullptr;
        }

        const Error * Pop::free() {
          return Globals::popMemPool.free(this);
        }

        void Pop::run(const f_done & done) {
          Globals::timeout.timeout = Timeout::NO_TIMEOUT;
          done(Globals::depth.pop());
          return;
        }

  }
}

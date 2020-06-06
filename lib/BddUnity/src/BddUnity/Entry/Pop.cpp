#include "Pop.hpp"

namespace BddUnity {
  namespace Entry {

        Pop * Pop::create(Context::Interface & context) {
          MemPool::Interface & memPool = context.getPopMemPool();
          void * address = memPool.alloc();
          if (address) {
            return new(address) Pop(context);
          }
          setStaticError(memPool.error);
          return nullptr;
        }

        const Error * Pop::free() {
          return _context.getPopMemPool().free(this);
        }

        void Pop::run(Timeout & timeout, const f_done & done) {
          timeout.timeout = Timeout::NO_TIMEOUT;
          done(_context.getDepth().pop());
          return;
        }

        Pop::Pop(Context::Interface & context) :
          Interface(context)
        {}

  }
}

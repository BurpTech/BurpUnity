#include "./Error.hpp"

namespace AsyncUnity {
  namespace Globals {

    const Error timeoutError(Error::Code::TIMEOUT);
    const Error maxDepthError(Error::Code::MAX_DEPTH);
    const Error minDepthError(Error::Code::MIN_DEPTH);
    const Error maxAllocError(Error::Code::MAX_ALLOC);
    const Error minAllocError(Error::Code::MIN_ALLOC);
    const Error freedAddressError(Error::Code::FREED_ADDRESS);
    const Error notAllocError(Error::Code::NOT_ALLOC);

  }
}

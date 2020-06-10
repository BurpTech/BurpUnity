#pragma once

namespace BddUnity {
  namespace Depth {

    class Frame {

      public:

        enum class CallbackType {
          NONE,
          SYNC,
          ASYNC
        };

        Frame(const char * label, const long timeout);
        Frame(const Frame & frame);

        const char * label;
        const long timeout;
        CallbackType beforeEach;
        CallbackType afterEach;
        bool hasLoop;

    };

  }
}

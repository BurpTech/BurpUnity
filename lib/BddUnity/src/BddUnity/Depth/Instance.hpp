#pragma once

#include <memory>
#include <stdio.h>
#include "Interface.hpp"

namespace BddUnity {
  namespace Depth {

    template <size_t maxDepth, size_t labelBufferSize, long defaultTimeout>
    class Instance : public Interface {
      
      public:

        const Error * push(const char * label, const long timeout) override {
          if (maxDepth == _current) {
            setError(Error::Code::MAX_DEPTH);
            return &error;
          }
          new(&(_frames[_current++])) Frame(label, timeout);
          highUsed = _current > highUsed ? _current : highUsed;
          return nullptr;
        }

        const Error * pop() override {
          if (0 == _current) {
            setError(Error::Code::MIN_DEPTH);
            return &error;
          }
          _current--;
          return nullptr;
        }

        const char * getLabel(const char * field) override {
          _resetLabel();
          _concatenateLabel(field);
          return _currentLabel;
        }

        const char * getLabel(const char * field1, const char * field2) override {
          _resetLabel();
          _concatenateLabel(field1);
          _concatenateLabel(field2);
          return _currentLabel;
        }

        const long getTimeout(const long timeout) override {
          if (0 != timeout) {
            // timeout has been overriden
            return timeout;
          }
          long ret = defaultTimeout;
          for (int i = 0; i < _current; i++) {
            // only apply next timeout if it is an override
            const long t = _frames[i].timeout;
            if (0 != t) {
              ret = t;
            }
          }
          return ret;
        }

      private:

        struct Frame {
          Frame(const char * label, const long timeout) :
            label(label),
            timeout(timeout)
          {}
          const char * label;
          const long timeout;
        };

        std::allocator<Frame> allocator;
        Frame * _frames = allocator.allocate(maxDepth);
        size_t _current = 0;

        // we use 2 buffers to make concatenation simpler
        char _label1[labelBufferSize];
        char _label2[labelBufferSize];
        char * _currentLabel;

        void _resetLabel() {
          _currentLabel = _label1;
          _currentLabel[0] = 0;
          for (int i = 0; i < _current; i++) {
            _concatenateLabel(_frames[i].label);
          }
        }

        void  _concatenateLabel(const char * field) {
          char * destination = _currentLabel == _label1 ? _label2 : _label1;
          snprintf(destination, labelBufferSize, "%s[%s]", _currentLabel, field);
          _currentLabel = destination;
        }

    };

  }
}

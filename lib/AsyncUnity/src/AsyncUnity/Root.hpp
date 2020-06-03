#pragma once

#include <unity.h>
#include "./Describe.hpp"
#include "Type.hpp"

namespace AsyncUnity {

  class Root {
    
    public:

      bool running;
      int status;

      Root(
        const char * file,
        const size_t testNameBufferSize,
        const char * thing,
        Describe::f_describe cb,
        const unsigned long timeout = 0
      ) :
        running(true),
        status(0),
        _root(new Describe(thing, cb)),
        _file(file),
        _timeout(timeout),
        _testNameBufferSize(testNameBufferSize),
        _testName1(new char[_testNameBufferSize]),
        _testName2(new char[_testNameBufferSize]),
        _currentTestName(_testName1)
      {}

      ~Root() {
        delete[] _testName1;
        delete[] _testName2;
      }

      void setup() {
        UnityBegin(_file);
      }

      void loop() {
        _resetTestName();
        Entry * next = _loop(_root);
        if (!next) {
          _end();
        }
      }

    private:

      Describe * _root;
      const char * _file;
      const unsigned long _timeout;

      // we use 2 buffers to make concatenation simpler
      const size_t _testNameBufferSize;
      char * _testName1;
      char * _testName2;
      char * _currentTestName;

      void _resetTestName() {
        _currentTestName = _testName1;
        _currentTestName[0] = 0;
      }

      void  _concatenateTestName(const char * field) {
        char * destination = _currentTestName == _testName1 ? _testName2 : _testName1;
        snprintf(destination, _testNameBufferSize, "%s[%s]", _currentTestName, field);
        _currentTestName = destination;
      }

      void _end() {
        status = UnityEnd();
        running = false;
      }

      Entry * _loop(Entry * entry) {
        if (entry != nullptr) {
          switch (entry->type) {
            case Type::IT:
              {
                It * it = entry->as<It>();
                _concatenateTestName(it->should);
                UnityDefaultTestRun(it->sync, _currentTestName, it->line);
                Entry * next = it->next;
                delete it;
                return next;
              }
            case Type::DESCRIBE:
              {
                Describe * describe = entry->as<Describe>();
                if (describe->cb) {
                  describe->cb(describe);
                  describe->cb = nullptr;
                }
                _concatenateTestName(describe->thing);
                Entry * next = _loop(describe->entries);
                if (next) {
                  describe->entries = next;
                  return describe;
                } else {
                  next = describe->next;
                  delete describe;
                  return next;
                }
              }
          }
        }
        return nullptr;
      }

  };

}

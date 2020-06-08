#pragma once

#include "../../Memory/Pool/HasPool.hpp"
#include "../Interface.hpp"
#include "../List.hpp"
#include "../It/Params.hpp"
#include "../AsyncIt/Params.hpp"
#include "../Callback/Params.hpp"
#include "../AsyncCallback/Params.hpp"
#include "Params.hpp"

#define BDD_UNITY_ENTRY_DESCRIBE_DECLARE_CALLBACK(NAME)\
  void NAME(const int line, const Callback::Params::f_callback cb);\
  void NAME(const Callback::Params::f_callback cb);\
  void NAME(const int line, const AsyncCallback::Params::f_async cb, const long timeout = Timeout::INHERIT_TIMEOUT);\
  void NAME(const AsyncCallback::Params::f_async cb, const long timeout = Timeout::INHERIT_TIMEOUT)

namespace BddUnity {
  namespace Entry {
    namespace Describe {

      class Instance : public Interface, public Memory::Pool::HasPool<Interface, Params> {

        public:

          Instance(Memory::Pool::Interface<Interface, Params> * pool, const Params & params);

          BDD_UNITY_ENTRY_DESCRIBE_DECLARE_CALLBACK(before);
          BDD_UNITY_ENTRY_DESCRIBE_DECLARE_CALLBACK(after);
          BDD_UNITY_ENTRY_DESCRIBE_DECLARE_CALLBACK(beforeEach);
          BDD_UNITY_ENTRY_DESCRIBE_DECLARE_CALLBACK(afterEach);

          void describe(const char * thing, const Params::f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);
          void describe(const char * thing, const int line, const Params::f_describe describe, const long timeout = Timeout::INHERIT_TIMEOUT);

          void async(const char * should, const AsyncIt::Params::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);
          void async(const char * should, const int line, const AsyncIt::Params::f_async it, const long timeout = Timeout::INHERIT_TIMEOUT);

          void it(const char * should, const It::Params::f_testCallback it);
          void it(const char * should, const int line, const It::Params::f_testCallback it);

        private:

          const Params _params;
          List _list;

          void _run(List & list, Depth::Interface & depth, Timeout & timeout, const f_done & done) override;
          void _addTest(Interface * entry, const char * label, const int line);
          const Error * _free() override;
          const Error * free() override;

      };

    }
  }
}

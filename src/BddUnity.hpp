#pragma once

#include "BddUnity/defines.hpp"
#include "BddUnity/Entry/AsyncIt/Params.hpp"
#include "BddUnity/Runnable.hpp"
#include "BddUnity/Runner.hpp"
#include "BddUnity/Memory/Instance.hpp"
#include "BddUnity/Module.hpp"

#define bu_params(S) S, __LINE__

#if BDD_UNITY_SHORT_NAMES > 0

#define bup(S) bu_params(S)

using Memory = BddUnity::Memory::Instance<
BDD_UNITY_LABEL_BUFFER_SIZE,
BDD_UNITY_DEFAULT_TIMEOUT,
BDD_UNITY_SAFE_MEM_POOLS,
BDD_UNITY_MAX_MODULE,
BDD_UNITY_MAX_DEPTH,
BDD_UNITY_MAX_DESCRIBE,
BDD_UNITY_MAX_POP,
BDD_UNITY_MAX_TEST,
BDD_UNITY_MAX_IT,
BDD_UNITY_MAX_ASYNC_IT,
BDD_UNITY_MAX_CALLBACK,
BDD_UNITY_MAX_ASYNC_CALLBACK,
BDD_UNITY_MAX_STACKED_CALLBACK,
BDD_UNITY_MAX_STACKED_ASYNC_CALLBACK,
BDD_UNITY_MAX_BEFORE_EACH,
BDD_UNITY_MAX_ASYNC_BEFORE_EACH,
BDD_UNITY_MAX_AFTER_EACH,
BDD_UNITY_MAX_ASYNC_AFTER_EACH,
BDD_UNITY_MAX_SETUP,
BDD_UNITY_MAX_LOOP
>;
using Runnable = BddUnity::Runnable;
using Runner = BddUnity::Runner;
using Module = BddUnity::Module;
using Describe = BddUnity::Entry::Describe::Instance;
using f_done = BddUnity::Entry::AsyncIt::Params::f_done;
using Async = BddUnity::Entry::AsyncIt::Async;

#endif

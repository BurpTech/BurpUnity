#pragma once

#include "BddUnity/defines.hpp"
#include "BddUnity/Context/Instance.hpp"
#include "BddUnity/Module.hpp"

#define bu_params(S) S, __LINE__

#if BDD_UNITY_SHORT_NAMES > 0

#define bup(S) bu_params(S)

using Context = BddUnity::Context::Instance<
BDD_UNITY_LABEL_BUFFER_SIZE,
BDD_UNITY_DEFAULT_TIMEOUT,
BDD_UNITY_SAFE_MEM_POOLS,
BDD_UNITY_MAX_DEPTH,
BDD_UNITY_MAX_DESCRIBES,
BDD_UNITY_MAX_ITS,
BDD_UNITY_MAX_ASYNC_ITS
>;
using Module = BddUnity::Module;
using Describe = BddUnity::Entry::Describe;
using f_done = BddUnity::Entry::AsyncIt::f_done;
using Async = BddUnity::Entry::AsyncIt::Async;

#endif

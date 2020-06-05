#pragma once

#include "AsyncUnity/defines.hpp"
#include "AsyncUnity/Module.hpp"

#define au_params(S) S, __LINE__
#define au_module_params(S) __FILE__, au_params(S)

#if ASYNC_UNITY_SHORT_NAMES > 0

#define aup(S) au_params(S)
#define aump(S) au_module_params(S)

using Module = AsyncUnity::Module;
using Describe = AsyncUnity::Entry::Describe;
using f_done = AsyncUnity::Entry::AsyncIt::f_done;
using Async = AsyncUnity::Entry::AsyncIt::Async;

#endif

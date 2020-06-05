#pragma once

#include "AsyncUnity/defines.hpp"
#include "AsyncUnity/Root.hpp"

#define au_params(S) S, __LINE__
#define au_root_params(S) __FILE__, au_params(S)

#if ASYNC_UNITY_SHORT_NAMES > 0

#define aup(S) au_params(S)
#define aurp(S) au_root_params(S)

using Root = AsyncUnity::Root;
using Describe = AsyncUnity::Entry::Describe;
using f_done = AsyncUnity::Entry::AsyncIt::f_done;
using Async = AsyncUnity::Entry::AsyncIt::Async;

#endif

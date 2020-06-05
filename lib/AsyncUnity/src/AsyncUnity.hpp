#pragma once

#include "AsyncUnity/defines.hpp"
#include "AsyncUnity/Root.hpp"

#if ASYNC_UNITY_SHORT_NAMES > 0

using Root = AsyncUnity::Root;
using Describe = AsyncUnity::Entry::Describe;
using f_done = AsyncUnity::Entry::AsyncIt::f_done;
using f_test = AsyncUnity::Entry::AsyncIt::f_test;

#define NAME(S) S, __LINE__
#define ROOT_NAME(S) __FILE__, NAME(S)

#endif

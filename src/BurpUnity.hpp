#pragma once

#include "BurpUnity/defines.hpp"
#include "BurpUnity/Entry/AsyncIt/Params.hpp"
#include "BurpUnity/Runnable.hpp"
#include "BurpUnity/Runner.hpp"
#include "BurpUnity/Memory/Instance.hpp"
#include "BurpUnity/Module.hpp"
#include "BurpUnity/Usage.hpp"
#include <cstddef>

#define bu_params(S) S, __LINE__

#if BURP_UNITY_SHORT_NAMES > 0

#define bup(S) bu_params(S)

using Memory = BurpUnity::Memory::Instance<
BURP_UNITY_LABEL_BUFFER_SIZE,
BURP_UNITY_DEFAULT_TIMEOUT,
BURP_UNITY_SAFE_MEM_POOLS,
BURP_UNITY_MAX_MODULE,
BURP_UNITY_MAX_DEPTH,
BURP_UNITY_MAX_DESCRIBE,
BURP_UNITY_MAX_POP,
BURP_UNITY_MAX_TEST,
BURP_UNITY_MAX_IT,
BURP_UNITY_MAX_ASYNC_IT,
BURP_UNITY_MAX_CALLBACK,
BURP_UNITY_MAX_ASYNC_CALLBACK,
BURP_UNITY_MAX_STACKED_CALLBACK,
BURP_UNITY_MAX_STACKED_ASYNC_CALLBACK,
BURP_UNITY_MAX_BEFORE_EACH,
BURP_UNITY_MAX_ASYNC_BEFORE_EACH,
BURP_UNITY_MAX_AFTER_EACH,
BURP_UNITY_MAX_ASYNC_AFTER_EACH,
BURP_UNITY_MAX_SETUP,
BURP_UNITY_MAX_LOOP
>;
using Runnable = BurpUnity::Runnable;
template <size_t size>
using Runnables = BurpUnity::Runnables<size>;
template <size_t size>
using Runner = BurpUnity::Runner<size>;
using Module = BurpUnity::Module;
using Describe = BurpUnity::Entry::Describe::Instance;
using f_done = BurpUnity::Entry::AsyncIt::Params::f_done;
using Async = BurpUnity::Entry::AsyncIt::Async;

#endif

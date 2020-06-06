#pragma once

#include "BddUnity/defines.hpp"
#include "BddUnity/Module.hpp"

#define bu_params(S) S, __LINE__

#if BDD_UNITY_SHORT_NAMES > 0

#define bup(S) bu_params(S)

using Module = BddUnity::Module;
using Describe = BddUnity::Entry::Describe;
using f_done = BddUnity::Entry::AsyncIt::f_done;
using Async = BddUnity::Entry::AsyncIt::Async;

#endif

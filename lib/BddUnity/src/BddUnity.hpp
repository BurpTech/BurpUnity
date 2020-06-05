#pragma once

#include "BddUnity/defines.hpp"
#include "BddUnity/Module.hpp"

#define bu_params(S) S, __LINE__
#define bu_module_params(S) __FILE__, bu_params(S)

#if BDD_UNITY_SHORT_NAMES > 0

#define bup(S) bu_params(S)
#define bump(S) bu_module_params(S)

using Module = BddUnity::Module;
using Describe = BddUnity::Entry::Describe;
using f_done = BddUnity::Entry::AsyncIt::f_done;
using Async = BddUnity::Entry::AsyncIt::Async;

#endif

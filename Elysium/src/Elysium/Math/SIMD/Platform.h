#pragma once

#if defined(_MSVC_LANG)  // MS compiler has its own version of __cplusplus with different value
#if _MSVC_LANG < 201703
#error Please compile for C++17 or higher
#endif
#else  // all other compilers
#if __cplusplus < 201703
#error Please compile for C++17 or higher
#endif
#endif

#if defined(__AVX512F__)
#define SIMD_LEVEL_AVX512 1
#elif defined(__AVX2__)
#define SIMD_LEVEL_AVX2 1
#elif defined(__AVX__)
#define SIMD_LEVEL_AVX 1
#elif defined(__SSE4_1__)
#define SIMD_LEVEL_SSE41 1
#else
#define SIMD_LEVEL_SCALAR 1
#endif

#if SIMD_LEVEL_AVX512 || SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
#include <immintrin.h>
#include <xmmintrin.h>
#elif SIMD_LEVEL_SSE41
#include <smmintrin.h>
#include <xmmintrin.h>
#else
#include <cmath>  // Scalar fallback
#endif

/*
* #if GLM_ARCH & GLM_ARCH_AVX2_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_AVX_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE42_BIT
#	if GLM_COMPILER & GLM_COMPILER_CLANG
#		include <popcntintrin.h>
#	endif
#	include <nmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE41_BIT
#	include <smmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSSE3_BIT
#	include <tmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE3_BIT
#	include <pmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE2_BIT
#	include <emmintrin.h>
#elif GLM_ARCH & GLM_ARCH_NEON_BIT
#	include "neon.h"
#endif//GLM_ARCH

*/
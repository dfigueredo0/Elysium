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

// Architecture detection
#if defined(__aarch64__) || defined(__arm__) || defined(_M_ARM) || defined(_M_ARM64)
#define SIMD_ARCH_ARM 1
#else
#define SIMD_ARCH_X86 1
#endif

// SIMD level detection
#if SIMD_ARCH_X86
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
#elif SIMD_ARCH_ARM
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#define SIMD_NEON 1
#else
#define SIMD_LEVEL_SCALAR 1
#endif
#else
#define SIMD_LEVEL_SCALAR 1
#endif

// Include SIMD headers
#if SIMD_LEVEL_AVX512 || SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
#include <immintrin.h>
#elif SIMD_LEVEL_SSE41
#include <smmintrin.h>
#elif SIMD_NEON
#include "Neon.h"
#else
#include <cmath>  // Scalar fallback
#endif
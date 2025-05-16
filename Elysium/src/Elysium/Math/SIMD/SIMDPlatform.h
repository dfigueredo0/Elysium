#pragma once

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
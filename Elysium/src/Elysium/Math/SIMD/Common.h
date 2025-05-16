#pragma once

#include "Platform.h"

#if SIMD_LEVEL_AVX512 || SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
#include <immintrin.h>
#elif SIMD_LEVEL_SSE41
#include <smmintrin.h>
#include <xmmintrin.h>
#else
#include <cmath>  // Scalar fallback
#endif
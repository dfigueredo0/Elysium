#pragma once

#include "Elysium/Core.h"
#include "Platform.h"

INLINE __m128i floatToInt(__m128 a) {
    return _mm_cvtps_epi32(a);
}

INLINE __m128 intToFloat(__m128i a) {
    return _mm_cvtepi32_ps(a);
}

// TODO: vector conversions
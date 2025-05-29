#pragma once

#include "Elysium/Core.h"

#include "Platform.h"

namespace SIMD {
    INLINE __m128i addInt(__m128i a, __m128i b) {
        return _mm_add_epi32(a, b);
    }

    INLINE __m128i mulInt(__m128i a, __m128i b) {
        return _mm_mullo_epi32(a, b);
    }
}
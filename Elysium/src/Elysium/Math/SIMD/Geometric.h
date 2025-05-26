#pragma once

#include "Elysium/Core.h"
#include "Common.h"

INLINE __m128 dot(__m128 u, __m128 v) {
    __m128 mul = _mm_mul_ps(u, v);
    return _mm_add_ps(mul, _mm_movehl_ps(mul, mul)); 
}

INLINE __m128 cross(__m128 u, __m128 v) {
    // You’ll need to manually swizzle and multiply
}

INLINE __m256d dot(__m256d u, __m256d v) {
    __m256d mul = _mm256_mul_pd(u, v);
    __m128d hi = _mm256_extractf128_pd(mul, 1);
    __m128d lo = _mm256_castpd256_pd128(mul);
    __m128d sum = _mm_add_pd(lo, hi);
    sum = _mm_hadd_pd(sum, sum);
    return _mm256_castpd128_pd256(sum);
}

INLINE __m256d cross(__m256d u, __m256d v) {
    // You’ll need to manually swizzle and multiply
}

INLINE __m128 squared_length(__m128 u) {
    return dot(u, u);
}

INLINE __m256d squared_length(__m256d u) {
    return dot(u, u);
}

INLINE __m128 length(__m128 u) {
    return _mm_sqrt_ps(squared_length(u));
}

INLINE __m256d length(__m256d u) {
    return _mm256_sqrt_pd(squared_length(u));
}

INLINE __m128 normalize(__m128 u) {

}

INLINE __m256d normalize(__m256d u) {

}

INLINE __m128 distance(__m128 u, __m128 v) {

}

INLINE __m256d distance(__m256d u, __m256d v) {

}

INLINE __m128 forward(__m128 normal, __m128 identity, __m128 reference) {

}

INLINE __m256d forward(__m256d normal, __m256d identity, __m256d reference) {

}

INLINE __m128 reflect(__m128 identity, __m128 normal) {

}

INLINE __m256d reflect(__m256d identity, __m256d normal) {

}

INLINE __m128 refract(__m128 identity, __m128 normal, __m128 eta) {

}

INLINE __m256d refract(__m256d identity, __m256d normal, __m256d eta) {

}

INLINE __m128 project(__m128 u, __m128 v) {

}

INLINE __m128 angle_between(__m128 u, __m128 v) {

}
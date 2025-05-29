#pragma once

#include "Elysium/Core.h"
#include "Common.h"
#include "Trigonometric.h"

namespace SIMD {
    INLINE __m128 dot3(__m128 u, __m128 v) {
        // Mask w to zero
        __m128 mask = _mm_castsi128_ps(_mm_set_epi32(0, -1, -1, -1));
        u = _mm_and_ps(u, mask);
        v = _mm_and_ps(v, mask);
        __m128 mul = _mm_mul_ps(u, v);
        __m128 shuf = _mm_movehdup_ps(mul); // y z w w
        __m128 sums = _mm_add_ps(mul, shuf); // x+y z+w
        shuf = _mm_movehl_ps(shuf, sums);
        return _mm_add_ss(sums, shuf); // x+y+z
    }

    INLINE __m256d dot3(__m256d u, __m256d v) {
        // Mask upper lane
        __m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
        u = _mm256_and_pd(u, _mm256_castsi256_pd(mask));
        v = _mm256_and_pd(v, _mm256_castsi256_pd(mask));
        __m256d mul = _mm256_mul_pd(u, v);
        __m128d lo = _mm256_castpd256_pd128(mul);
        __m128d hi = _mm256_extractf128_pd(mul, 1);
        __m128d sum = _mm_add_pd(lo, hi);
        return _mm256_castpd128_pd256(_mm_hadd_pd(sum, sum));
    }

    INLINE __m128 dot(__m128 u, __m128 v) {
        __m128 mul = _mm_mul_ps(u, v);
        return _mm_add_ps(mul, _mm_movehl_ps(mul, mul));
    }

    INLINE __m256d dot(__m256d u, __m256d v) {
        __m256d mul = _mm256_mul_pd(u, v);
        __m128d hi = _mm256_extractf128_pd(mul, 1);
        __m128d lo = _mm256_castpd256_pd128(mul);
        __m128d sum = _mm_add_pd(lo, hi);
        sum = _mm_hadd_pd(sum, sum);
        return _mm256_castpd128_pd256(sum);
    }

    INLINE __m128 cross(__m128 u, __m128 v) {
        __m128 u_yzx = _mm_shuffle_ps(u, u, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 v_yzx = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 cross = _mm_sub_ps(_mm_mul_ps(u, v_yzx), _mm_mul_ps(u_yzx, v));
        return _mm_shuffle_ps(cross, cross, _MM_SHUFFLE(3, 0, 2, 1));
    }

    INLINE __m256d cross(__m256d u, __m256d v) {
        __m256d u_yzx = _mm256_permute4x64_pd(u, _MM_SHUFFLE(3, 0, 2, 1));
        __m256d v_yzx = _mm256_permute4x64_pd(v, _MM_SHUFFLE(3, 0, 2, 1));
        __m256d cross = _mm256_sub_pd(_mm256_mul_pd(u, v_yzx), _mm256_mul_pd(u_yzx, v));
        return _mm256_permute4x64_pd(cross, _MM_SHUFFLE(3, 0, 2, 1));
    }

    INLINE __m128 squared_length(__m128 u) {
        return dot(u, u);
    }

    INLINE __m256d squared_length(__m256d u) {
        return dot(u, u);
    }

    INLINE __m128 length3(__m128 u) {
        return _mm_sqrt_ps(dot3(u, u));
    }

    INLINE __m256d length3(__m256d u) {
        return _mm256_sqrt_pd(dot3(u, u));
    }

    INLINE __m128 length(__m128 u) {
        return _mm_sqrt_ps(squared_length(u));
    }

    INLINE __m256d length(__m256d u) {
        return _mm256_sqrt_pd(squared_length(u));
    }

    INLINE __m128 normalize3(__m128 u) {
        __m128 mask = _mm_castsi128_ps(_mm_set_epi32(0, -1, -1, -1));
        u = _mm_and_ps(u, mask);
        __m128 length = _mm_sqrt_ps(dot3(u, u));
        return _mm_div_ps(u, length);
    }

    INLINE __m256d normalize3(__m256d u) {
        __m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
        u = _mm256_and_pd(u, _mm256_castsi256_pd(mask));
        __m256d length = _mm256_sqrt_pd(dot3(u, u));
        return _mm256_div_pd(u, length);
    }

    INLINE __m128 normalize(__m128 u) {
        return _mm_div_ps(u, length(u));
    }

    INLINE __m256d normalize(__m256d u) {
        return _mm256_div_pd(u, length(u));
    }

    INLINE __m128 distance(__m128 u, __m128 v) {
        __m128 d = _mm_sub_ps(u, v);
        return length(d);
    }

    INLINE __m256d distance(__m256d u, __m256d v) {
        __m256d d = _mm256_sub_pd(u, v);
        return length(d);
    }

    INLINE __m128 forward(__m128 normal, __m128 reference) {
        __m128 proj = project(reference, normal);
        return normalize(_mm_sub_ps(reference, proj));
    }

    INLINE __m256d forward(__m256d normal, __m256d reference) {
        __m256d proj = project(reference, normal);
        return normalize(_mm256_sub_pd(reference, proj));
    }

    INLINE __m128 reflect(__m128 identity, __m128 normal) {
        __m128 two = _mm_set1_ps(2.0f);
        return _mm_sub_ps(identity, _mm_mul_ps(two, _mm_mul_ps(dot(identity, normal), normal)));
    }

    INLINE __m256d reflect(__m256d identity, __m256d normal) {
        __m256d two = _mm256_set1_pd(2.0);
        return _mm256_sub_pd(identity, _mm256_mul_pd(two, _mm256_mul_pd(dot(identity, normal), normal)));
    }

    INLINE __m128 refract(__m128 identity, __m128 normal, __m128 eta) {
        __m128 dotNI = dot(identity, normal);
        __m128 k = _mm_mul_ps(_mm_sub_ps(_mm_set1_ps(1.0f), _mm_mul_ps(eta, eta)), _mm_sub_ps(_mm_set1_ps(1.0f), _mm_mul_ps(dotNI, dotNI)));
        __m128 mask = _mm_cmpge_ps(k, _mm_setzero_ps());
        __m128 sqrtK = _mm_sqrt_ps(k);
        return _mm_blendv_ps(_mm_setzero_ps(), _mm_sub_ps(_mm_mul_ps(eta, identity), _mm_mul_ps(_mm_add_ps(_mm_mul_ps(eta, dotNI), sqrtK), normal)), mask);
    }

    INLINE __m256d refract(__m256d identity, __m256d normal, __m256d eta) {
        __m256d dotNI = dot(identity, normal);
        __m256d one = _mm256_set1_pd(1.0);
        __m256d k = _mm256_mul_pd(_mm256_sub_pd(one, _mm256_mul_pd(eta, eta)), _mm256_sub_pd(one, _mm256_mul_pd(dotNI, dotNI)));
        __m256d mask = _mm256_cmp_pd(k, _mm256_setzero_pd(), _CMP_GE_OQ);
        __m256d sqrtK = _mm256_sqrt_pd(k);
        return _mm256_blendv_pd(_mm256_setzero_pd(), _mm256_sub_pd(_mm256_mul_pd(eta, identity), _mm256_mul_pd(_mm256_add_pd(_mm256_mul_pd(eta, dotNI), sqrtK), normal)), mask);
    }

    INLINE __m128 project(__m128 u, __m128 v) {
        return _mm_mul_ps(dot(u, v), _mm_div_ps(v, dot(v, v)));
    }

    INLINE __m256d project(__m256d u, __m256d v) {
        return _mm256_mul_pd(dot(u, v), _mm256_div_pd(v, dot(v, v)));
    }

    INLINE __m128 angle_between(__m128 u, __m128 v) {
        __m128 d = dot(normalize(u), normalize(v));
        return acos(d);
    }

    INLINE __m256d angle_between(__m256d u, __m256d v) {
        __m256d d = dot(normalize(u), normalize(v));
        return acos(d);
    }
}
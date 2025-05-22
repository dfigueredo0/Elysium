#pragma once

#include "Platform.h"

__m128 fmadd(__m128 a, __m128 b, __m128 c) {
	return _mm_add_ps(_mm_mul_ps(a, b), c);
}

__m128 div_lowp(__m128 a, __m128 b) {
	return _mm_mul_ps(a, _mm_rcp_ps(b));
}

__m256d div_lowp(__m256d a, __m256d b) {
	return _mm256_mul_pd(a, _mm256_rcp14_pd(b));
}

__m128 swizzle_xywz(__m128 a) {
#if SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
	return _mm_permute_ps(a, _MM_SHUFFLE(3, 2, 1, 0));
#else
	return _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 2, 1, 0)); // 0b11100100 0xE4
#endif  
}

__m256d swizzle_xywz(__m256d a) {
	return _mm256_permute_pd(a, _MM_SHUFFLE(3, 2, 1, 0));
}

__m128 round_even(__m128 a) {
	__m128 const sign = _mm_castsi128_ps(_mm_set1_epi32(int(0x800000)));
	__m128 const and = _mm_and_ps(sign, a);
	__m128 const or = _mm_or_ps(and, _mm_set_ps1(0x800000));
	__m128 const add = _mm_add_ps(a, or);
	return _mm_sub_ps(add, or);
}

__m256d round_even(__m256d a) {
	__m256d const sign = _mm256_castsi256_pd(_mm256_set1_epi32(int(0x800000ULL)));
	__m256d const and = _mm256_and_pd(sign, a);
	__m256d const or = _mm256_or_pd(and, _mm256_set1_pd(0x800000ULL));
	__m256d const add = _mm256_add_pd(a, or );
	return _mm256_sub_pd(add, or );
}

__m128 clamp(__m128 a, __m128 min, __m128 max) {
	return _mm_max_ps(_mm_min_ps(a, max), min);
}

__m256d clamp(__m256d a, __m256d min, __m256d max) {
	return _mm256_max_pd(_mm256_min_pd(a, max), min);
}

__m128 mix(__m128 a, __m128 b, __m128 c) {
	__m128 const sub = _mm_sub_ps(_mm_set1_ps(1.0f), c);
	__m128 const mul = _mm_mul_ps(a, sub);
	return fmadd(b, c, mul);
}

__m256d mix(__m256d a, __m256d b, __m256d c) {
	__m256d const sub = _mm256_sub_pd(_mm256_set1_pd(1.0), c);
	__m256d const mul = _mm256_mul_pd(a, sub);
	return _mm256_fmadd_pd(b, c, mul);
}

__m128 step(__m128 e, __m128 x) {

}

__m256d step(__m256d e, __m256d x) {

}

__m128 smoothStep(__m128 e, __m128 x) {

}

__m256d smoothStep(__m256d e, __m256d x) {

}

__m128 nan(__m128 x) {

}

__m256d nan(__m256d x) {

}

__m128 inf(__m128 x) {

}

__m256d inf(__m256d x) {

}
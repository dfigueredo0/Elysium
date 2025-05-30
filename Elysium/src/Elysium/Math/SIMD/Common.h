#pragma once

#include "Elysium/Core.h"

#include "Platform.h"

namespace SIMD {
	INLINE __m128 fmadd(__m128 a, __m128 b, __m128 c) {
		return _mm_add_ps(_mm_mul_ps(a, b), c);
	}

	INLINE __m128 div_lowp(__m128 a, __m128 b) {
		return _mm_mul_ps(a, _mm_rcp_ps(b));
	}

	INLINE __m256d div_lowp(__m256d a, __m256d b) {
		return _mm256_mul_pd(a, _mm256_rcp14_pd(b));
	}

	INLINE __m128 swizzle_xywz(__m128 a) {
#if SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
		return _mm_permute_ps(a, 0b0101);
#else
		return _mm_shuffle_ps(a, a, 0xE4);
#endif  
	}

	INLINE __m256d swizzle_xywz(__m256d a) {
		return _mm256_permute_pd(a, 0b0101);
	}

	INLINE __m128 round_even(__m128 a) {
		__m128 const sign = _mm_castsi128_ps(_mm_set1_epi32(int(0x800000)));
		__m128 const and = _mm_and_ps(sign, a);
		__m128 const or = _mm_or_ps(and, _mm_set_ps1(0x800000));
		__m128 const add = _mm_add_ps(a, or );
		return _mm_sub_ps(add, or );
	}

	INLINE __m256d round_even(__m256d a) {
		__m256d const sign = _mm256_castsi256_pd(_mm256_set1_epi32(int(0x800000ULL)));
		__m256d const and = _mm256_and_pd(sign, a);
		__m256d const or = _mm256_or_pd(and, _mm256_set1_pd(0x800000ULL));
		__m256d const add = _mm256_add_pd(a, or );
		return _mm256_sub_pd(add, or );
	}

	INLINE __m128 mod(__m128 a, __m128 b) {
		__m128 div = _mm_div_ps(a, b);
		__m128 div_trunc = _mm_round_ps(div, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
		return _mm_fnmadd_ps(div_trunc, b, a); 
	}

	INLINE __m256d mod(__m256d a, __m256d b) {
		__m256d div = _mm256_div_pd(a, b);
		__m256d div_trunc = _mm256_round_pd(div, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
		return _mm256_fnmadd_pd(div_trunc, b, a);
	}

	INLINE __m128 clamp(__m128 a, __m128 min, __m128 max) {
		return _mm_max_ps(_mm_min_ps(a, max), min);
	}

	INLINE __m256d clamp(__m256d a, __m256d min, __m256d max) {
		return _mm256_max_pd(_mm256_min_pd(a, max), min);
	}

	INLINE __m128 mix(__m128 a, __m128 b, __m128 c) {
		__m128 const sub = _mm_sub_ps(_mm_set1_ps(1.0f), c);
		__m128 const mul = _mm_mul_ps(a, sub);
		return fmadd(b, c, mul);
	}

	INLINE __m256d mix(__m256d a, __m256d b, __m256d c) {
		__m256d const sub = _mm256_sub_pd(_mm256_set1_pd(1.0), c);
		__m256d const mul = _mm256_mul_pd(a, sub);
		return _mm256_fmadd_pd(b, c, mul);
	}

	INLINE __m128 step(__m128 e, __m128 x) {
		return _mm_cmpge_ps(x, e);
	}

	INLINE __m256d step(__m256d e, __m256d x) {
		return _mm256_cmp_pd(x, e, 0x1D);
	}

	INLINE __m128 lerp_unclamped(__m128 a, __m128 b, __m128 t) {
		return fmadd(_mm_sub_ps(b, a), t, a);
	}

	INLINE __m256d lerp_unclamped(__m256d a, __m256d b, __m256d t) {
		return _mm256_fmadd_pd(_mm256_sub_pd(b, a), t, a);
	}

	INLINE __m128 smooth_step(__m128 e, __m128 x) {
		__m128 const sub = _mm_sub_ps(x, e);
		__m128 const div = _mm_div_ps(sub, _mm_sub_ps(_mm_set1_ps(1.0f), e));
		__m128 const clmp = clamp(div, _mm_setzero_ps(), _mm_set1_ps(1.0f));
		__m128 const mul = _mm_mul_ps(_mm_set1_ps(2.0f), clmp);
		return _mm_mul_ps(_mm_mul_ps(clmp, clmp), _mm_sub_ps(_mm_set1_ps(3.0f), mul));
	}

	INLINE __m256d smooth_step(__m256d e, __m256d x) {
		__m256d const sub = _mm256_sub_pd(x, e);
		__m256d const div = _mm256_div_pd(sub, _mm256_sub_pd(_mm256_set1_pd(1.0), e));
		__m256d const clmp = clamp(div, _mm256_setzero_pd(), _mm256_set1_pd(1.0));
		__m256d const mul = _mm256_mul_pd(_mm256_set1_pd(2.0), clmp);
		return _mm256_mul_pd(_mm256_mul_pd(clmp, clmp), _mm256_sub_pd(_mm256_set1_pd(3.0), mul));
	}

	INLINE __m128 sign(__m128 a) {
		const __m128 zero = _mm_setzero_ps();
		const __m128 one = _mm_set1_ps(1.0f);
		const __m128 neg_one = _mm_set1_ps(-1.0f);

		__m128 is_pos = _mm_cmpgt_ps(a, zero);
		__m128 is_neg = _mm_cmplt_ps(a, zero);

		return _mm_or_ps(_mm_and_ps(is_pos, one), _mm_and_ps(is_neg, neg_one));
	}

	INLINE __m256d sign(__m256d a) {
		const __m256d zero = _mm256_setzero_pd();
		const __m256d one = _mm256_set1_pd(1.0);
		const __m256d neg_one = _mm256_set1_pd(-1.0);

		__m256d is_pos = _mm256_cmp_pd(a, zero, _CMP_GT_OQ);
		__m256d is_neg = _mm256_cmp_pd(a, zero, _CMP_LT_OQ);

		return _mm256_or_pd(_mm256_and_pd(is_pos, one), _mm256_and_pd(is_neg, neg_one));
	}
	
	INLINE int minIndex(__m128 a) {
		alignas(16) float val[4];
		_mm_store_ps(val, a);

		int minIdx = 0;
		float minVal = val[0];
		for (int i = 1; i < 4; ++i) {
			if (val[i] < minVal) {
				minVal = val[i];
				minIdx = i;
			}
		}
		return minIdx;
	}

	INLINE int maxIndex(__m128 a) {
		alignas(16) float val[4];
		_mm_store_ps(val, a);

		int maxIdx = 0;
		float maxVal = val[0];
		for (int i = 1; i < 4; ++i) {
			if (val[i] > maxVal) {
				maxVal = val[i];
				maxIdx = i;
			}
		}
		return maxIdx;
	}

	INLINE int minIndex(__m256d a) {
		alignas(32) double val[4];
		_mm256_store_pd(val, a);

		int minIdx = 0;
		double minVal = val[0];
		for (int i = 1; i < 4; ++i) {
			if (val[i] < minVal) {
				minVal = val[i];
				minIdx = i;
			}
		}
		return minIdx;
	}

	INLINE int maxIndex(__m256d a) {
		alignas(32) double val[4];
		_mm256_store_pd(val, a);

		int maxIdx = 0;
		double maxVal = val[0];
		for (int i = 1; i < 4; ++i) {
			if (val[i] > maxVal) {
				maxVal = val[i];
				maxIdx = i;
			}
		}
		return maxIdx;
	}

	INLINE __m128 abs_ps(__m128 a) {
		return _mm_and_ps(a, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
	}

	INLINE __m256d abs_pd(__m256d a) {
		return _mm256_and_pd(a, _mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFFULL)));
	}

	// Newton-Raphson refinement
	INLINE __m128 rsqrt_refined(__m128 a) {
		__m128 half = _mm_set1_ps(0.5f);
		__m128 three = _mm_set1_ps(3.0f);

		__m128 x = _mm_rsqrt14_ps(a);

		__m128 axx = _mm_mul_ps(a, _mm_mul_ps(x, x));
		return _mm_mul_ps(half, _mm_mul_ps(x, _mm_sub_ps(three, axx)));;
	}

	// Newton-Raphson refinement
	INLINE __m256d rsqrt_refined(__m256d a) {
		__m256d half = _mm256_set1_pd(0.5);
		__m256d three = _mm256_set1_pd(3.0);

		__m256d x = _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(a));

		__m256d axx = _mm256_mul_pd(a, _mm256_mul_pd(x, x));
		return _mm256_mul_pd(half, _mm256_mul_pd(x, _mm256_sub_pd(three, axx)));
	}

	// Agner Fod method
	INLINE __m128 nan(__m128 x) {
		__m128i bits = _mm_castps_si128(x);
		__m128i absBits = _mm_and_si128(bits, _mm_set1_epi32(0x7FFFFFFF)); // Clear sign bit
		__m128i expMask = _mm_set1_epi32(0x7F800000);                      // Exponent mask
		__m128i mantMask = _mm_set1_epi32(0x007FFFFF);                    // Mantissa mask

		__m128i isExpMax = _mm_cmpeq_epi32(_mm_and_si128(absBits, expMask), expMask);
		__m128i hasMant = _mm_cmpgt_epi32(_mm_and_si128(absBits, mantMask), _mm_setzero_si128());

		return _mm_castsi128_ps(_mm_and_si128(isExpMax, hasMant)); // Exponent max and mantissa non-zero -> NaN
	}

	// Agner Fod method
	INLINE __m256d nan(__m256d x) {
		__m256i bits = _mm256_castpd_si256(x);
		__m256i absBits = _mm256_and_si256(bits, _mm256_set1_epi64x(0x7FFFFFFFFFFFFFFFULL));
		__m256i expMask = _mm256_set1_epi64x(0x7FF0000000000000ULL);
		__m256i mantMask = _mm256_set1_epi64x(0x000FFFFFFFFFFFFFULL);

		__m256i isExpMax = _mm256_cmpeq_epi64(_mm256_and_si256(absBits, expMask), expMask);
		__m256i hasMant = _mm256_cmpgt_epi64(_mm256_and_si256(absBits, mantMask), _mm256_setzero_si256());

		return _mm256_castsi256_pd(_mm256_and_si256(isExpMax, hasMant));
	}

	// Agner Fod method
	INLINE __m128 inf(__m128 x) {
		__m128i bits = _mm_castps_si128(x);
		__m128i absBits = _mm_and_si128(bits, _mm_set1_epi32(0x7FFFFFFF)); // Clear sign bit

		__m128i isInf = _mm_cmpeq_epi32(absBits, _mm_set1_epi32(0x7F800000)); // All exponent bits set, zero mantissa
		return _mm_castsi128_ps(isInf);
	}

	// Agner Fod method
	INLINE __m256d inf(__m256d x) {
		__m256i bits = _mm256_castpd_si256(x);
		__m256i absBits = _mm256_and_si256(bits, _mm256_set1_epi64x(0x7FFFFFFFFFFFFFFFULL));

		__m256i isInf = _mm256_cmpeq_epi64(absBits, _mm256_set1_epi64x(0x7FF0000000000000ULL));
		return _mm256_castsi256_pd(isInf);
	}
}
#pragma once

#include "Common.h"

#include "../Constants.h"

namespace SIMD {
	/**
	* @brief Compute the natural logarithm of packed single-precision (32-bit) floating-point elements in a, 
	*		 and store the results in dst.
	*/
	INLINE __m128 log(__m128 x) {
		__m128i xi = _mm_castps_si128(x);
		__m128i exponent = _mm_srli_epi32(xi, 23);
		__m128 e = _mm_cvtepi32_ps(_mm_sub_epi32(exponent, _mm_set1_epi32(0x7F)));

		__m128 mantissa_bits = _mm_castsi128_ps(_mm_or_si128(
			_mm_and_si128(xi, _mm_set1_epi32(0x7FFFFF)),
			_mm_set1_epi32(0x3F800000)
		));

		__m128 y = _mm_sub_ps(mantissa_bits, _mm_set1_ps(1.0f));
		__m128 y2 = _mm_mul_ps(y, y);
		__m128 y3 = _mm_mul_ps(y2, y);
		__m128 y4 = _mm_mul_ps(y2, y2);
		__m128 y5 = _mm_mul_ps(y4, y);
		__m128 y6 = _mm_mul_ps(y5, y);

		__m128 poly = fmadd(y6, _mm_set1_ps(-1.0f / 6.0f),
			fmadd(y5, _mm_set1_ps(0.2f),
				fmadd(y4, _mm_set1_ps(-0.25f),
					fmadd(y3, _mm_set1_ps(1.0f / 3.0f),
						fmadd(y2, _mm_set1_ps(-0.5f), y)))));

		return fmadd(e, _mm_set1_ps(Math::MathTraits<float>::LN2), poly);
	}

	/**
	* @brief Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m256d log(__m256d x) {
		__m256i xi = _mm256_castpd_si256(x);
		__m256i exponent = _mm256_srli_epi64(xi, 52);
		__m256d e = _mm256_cvtepi64_pd(_mm256_sub_epi64(exponent, _mm256_set1_epi64x(0x3FF)));

		__m256d mantissa_bits = _mm256_castsi256_pd(_mm256_or_si256(
			_mm256_and_si256(xi, _mm256_set1_epi64x(0x000FFFFFFFFFFFFF)),
			_mm256_set1_epi64x(0x3FF0000000000000)
		));

		__m256d y = _mm256_sub_pd(mantissa_bits, _mm256_set1_pd(1.0));
		__m256d y2 = _mm256_mul_pd(y, y);
		__m256d y3 = _mm256_mul_pd(y2, y);
		__m256d y4 = _mm256_mul_pd(y3, y);
		__m256d y5 = _mm256_mul_pd(y4, y);
		__m256d y6 = _mm256_mul_pd(y5, y);

		__m256d poly = _mm256_fmadd_pd(y6, _mm256_set1_pd(-1.0 / 6.0),
			_mm256_fmadd_pd(y5, _mm256_set1_pd(0.2),
				_mm256_fmadd_pd(y4, _mm256_set1_pd(-0.25),
					_mm256_fmadd_pd(y3, _mm256_set1_pd(1.0 / 3.0),
						_mm256_fmadd_pd(y2, _mm256_set1_pd(-0.5), y)))));

		return _mm256_fmadd_pd(e, _mm256_set1_pd(Math::MathTraits<double>::LN2), poly);
	}
	 
	/**
	* @brief Compute the base-2 logarithm of packed single-precision (32-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m128 log2(__m128 x) {
		return _mm_mul_ps(log(x), _mm_set1_ps(Math::MathTraits<float>::LOG2_E));
	}

	/**
	* @brief Compute the base-2 logarithm of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m256d log2(__m256d x) {
		return _mm256_mul_pd(log(x), _mm256_set1_pd(Math::MathTraits<double>::LOG2_E));
	}


	/**
	* @brief Compute the base-10 logarithm of packed single-precision (32-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m128 log10(__m128 x) {
		return _mm_mul_ps(log(x), _mm_set1_ps(Math::MathTraits<float>::LOG10_E));
	}

	/**
	* @brief Compute the base-10 logarithm of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m256d log10(__m256d x) {
		return _mm256_mul_pd(log(x), _mm256_set1_pd(Math::MathTraits<double>::LOG10_E));
	}
}


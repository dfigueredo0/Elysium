#pragma once

#include "Common.h"
#include "Logarithmic.h"

#include "../Constants.h"

namespace SIMD {

	static const __m128 exp_coeffs[] = {
		_mm_set1_ps(1.0f),
		_mm_set1_ps(1.0f),
		_mm_set1_ps(0.5f),
		_mm_set1_ps(0.1666667),
		_mm_set1_ps(0.0416667f),
		_mm_set1_ps(0.0083333f),
		_mm_set1_ps(0.0013889f),
		_mm_set1_ps(0.0001984f)
	};

	static const __m256d expd_coeffs[] = {
		_mm256_set1_pd(1.0),
		_mm256_set1_pd(1.0),
		_mm256_set1_pd(0.5),
		_mm256_set1_pd(0.16666666666666665741),
		_mm256_set1_pd(0.04166666666666666435),
		_mm256_set1_pd(0.00833333333333333322),
		_mm256_set1_pd(0.00138888888888888894),
		_mm256_set1_pd(0.00019841269841269841)
	};

	/**
	* @brief Compute the exponential value of packed single-precision (32-bit) floating-point elements in a raised by packed elements in b, 
	*		 and store the results in dst.
	*/
	INLINE __m128 pow(__m128 a, __m128 b) {
		return exp(_mm_mul_ps(b, SIMD::log(a)));
	}


	/**
	* @brief Compute the exponential value of packed double-precision (64-bit) floating-point elements in a raised by packed elements in b,
	*		 and store the results in dst.
	*/
	INLINE __m256d pow(__m256d a, __m256d b) {
		return exp(_mm256_mul_pd(b, SIMD::log(a)));
	}

	/**
	* @brief Computre the exponential value of e raised to the power of packed single-precision (32-bit) floating-point elements in a
	*		 and store the results in dst.
	*/
	INLINE __m128 exp(__m128 x) {
		const __m128 ln2 = _mm_set1_ps(Math::MathTraits<float>::LN2);
		const __m128 inv_ln2 = _mm_set1_ps(Math::MathTraits<float>::LOG2_E);

		__m128 n = fmadd(x, inv_ln2, _mm_setzero_ps());
		n = round_even(n);
		__m128 r = fmadd(n, _mm_set1_ps(-Math::MathTraits<float>::LN2), x);

		__m128 exp_r = exp_fast(r);

		__m128i int_n = _mm_cvtps_epi32(n);
		__m128i pow2n = _mm_slli_epi32(_mm_add_epi32(int_n, _mm_set1_epi32(0x7F)), 23);
		__m128 scale = _mm_castsi128_ps(pow2n);
		return _mm_mul_ps(exp_r, scale);
	}

	/**
	* @brief Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point elements in a, 
	*		 and store the results in dst.
	*/
	INLINE __m256d exp(__m256d x) {
		const __m256d ln2 = _mm256_set1_pd(Math::MathTraits<double>::LN2);
		const __m256d inv_ln2 = _mm256_set1_pd(Math::MathTraits<double>::LOG2_E);

		__m256d n = _mm256_fmadd_pd(x, inv_ln2, _mm256_setzero_pd());
		n = round_even(n);
		__m256d r = _mm256_fmadd_pd(n, _mm256_set1_pd(-Math::MathTraits<double>::LN2), x);

		__m256d exp_r = exp_fast(r);

		__m256i int_n = _mm256_cvtpd_epi64(n);
		__m256i pow2n = _mm256_slli_epi64(_mm256_add_epi64(int_n, _mm256_set1_epi64x(0x3FF)), 52);
		__m256d scale = _mm256_castsi256_pd(pow2n);
		return _mm256_mul_pd(exp_r, scale);
	}

	/**
	* @brief Compute the exponential value of 2 raised to the power of packed single-precision (32-bit) floating-point elements in a, 
	*		 and store the results in dst.
	*/
	INLINE __m128 exp2(__m128 x) {
		__m128i n = _mm_cvtps_epi32(x);
		__m128 r = _mm_sub_ps(x, _mm_cvtepi32_ps(n));
		__m128 exp_r = exp_fast(_mm_mul_ps(r, _mm_set1_ps(Math::MathTraits<float>::LN2)));

		__m128i pow2n = _mm_slli_epi32(_mm_add_epi32(n, _mm_set1_epi32(0x7F)), 23);
		__m128 scale = _mm_castsi128_ps(pow2n);
		return _mm_mul_ps(exp_r, scale);
	}

	/**
	* @brief Compute the exponential value of 2 raised to the power of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst.
	*/
	INLINE __m256d exp2(__m256d x) {
		__m256i n = _mm256_cvtpd_epi64(x);
		__m256d r = _mm256_sub_pd(x, _mm256_cvtepi64_pd(n));
		__m256d exp_r = exp_fast(_mm256_mul_pd(r, _mm256_set1_pd(Math::MathTraits<double>::LN2)));
		
		__m256i pow2n = _mm256_slli_epi64(_mm256_add_epi64(n, _mm256_set1_epi64x(0x3FF)), 52);
		__m256d scale = _mm256_castsi256_pd(pow2n);
		return _mm256_mul_pd(exp_r, scale);
	}


	/**
	* @brief Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst, using Estrin's Scheme.
	*/
	INLINE __m128 exp_fast(__m128 x) {
		__m128 x2 = _mm_mul_ps(x, x);
		__m128 x4 = _mm_mul_ps(x2, x2);

		__m128 t0 = fmadd(exp_coeffs[7], x, exp_coeffs[6]);
		__m128 t1 = fmadd(exp_coeffs[5], x, exp_coeffs[4]);
		__m128 t2 = fmadd(exp_coeffs[3], x, exp_coeffs[2]);
		__m128 t3 = fmadd(exp_coeffs[1], x, exp_coeffs[0]);

		__m128 p0 = fmadd(t0, x2, t1);
		__m128 p1 = fmadd(t2, x2, t3);
		return fmadd(p0, x4, p1);
	}

	/**
	* @brief Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point elements in a,
	*		 and store the results in dst, using Estrin's Scheme.
	*/
	INLINE __m256d exp_fast(__m256d x) {
		__m256d x2 = _mm256_mul_pd(x, x);
		__m256d x4 = _mm256_mul_pd(x2, x2);

		__m256d t0 = _mm256_fmadd_pd(expd_coeffs[7], x, expd_coeffs[6]);
		__m256d t1 = _mm256_fmadd_pd(expd_coeffs[5], x, expd_coeffs[4]);
		__m256d t2 = _mm256_fmadd_pd(expd_coeffs[3], x, expd_coeffs[2]);
		__m256d t3 = _mm256_fmadd_pd(expd_coeffs[1], x, expd_coeffs[0]);

		__m256d p0 = _mm256_fmadd_pd(t0, x2, t1);
		__m256d p1 = _mm256_fmadd_pd(t2, x2, t3);
		return _mm256_fmadd_pd(p0, x4, p1);
	}
}
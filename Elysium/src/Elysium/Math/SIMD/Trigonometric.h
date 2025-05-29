#pragma once

#include "Common.h"

#include "../Constants.h"

namespace SIMD {
	static const __m128 sin_coeffs[] = {
		_mm_set1_ps(Math::MathTraits<float>::S1),
		_mm_set1_ps(Math::MathTraits<float>::S2),
		_mm_set1_ps(Math::MathTraits<float>::S3),
		_mm_set1_ps(Math::MathTraits<float>::S4),
		_mm_set1_ps(Math::MathTraits<float>::S5),
		_mm_set1_ps(Math::MathTraits<float>::S6),
		_mm_set1_ps(Math::MathTraits<float>::S7),
		_mm_set1_ps(Math::MathTraits<float>::S8)
	};

	static const __m128 cos_coeffs[] = {
		_mm_set1_ps(Math::MathTraits<float>::C1),
		_mm_set1_ps(Math::MathTraits<float>::C2),
		_mm_set1_ps(Math::MathTraits<float>::C3),
		_mm_set1_ps(Math::MathTraits<float>::C4),
		_mm_set1_ps(Math::MathTraits<float>::C5),
		_mm_set1_ps(Math::MathTraits<float>::C6),
		_mm_set1_ps(Math::MathTraits<float>::C7),
		_mm_set1_ps(Math::MathTraits<float>::C8)
	};

	static const __m128 atan_coeffs[] = {
		_mm_set1_ps(Math::MathTraits<float>::A1),
		_mm_set1_ps(Math::MathTraits<float>::A2),
		_mm_set1_ps(Math::MathTraits<float>::A3),
		_mm_set1_ps(Math::MathTraits<float>::A4),
		_mm_set1_ps(Math::MathTraits<float>::A5),
		_mm_set1_ps(Math::MathTraits<float>::A6),
		_mm_set1_ps(Math::MathTraits<float>::A7),
		_mm_set1_ps(Math::MathTraits<float>::A8)
	};

	static const __m256d sin_coeffs_d[] = {
		_mm256_set1_pd(Math::MathTraits<double>::S1),
		_mm256_set1_pd(Math::MathTraits<double>::S2),
		_mm256_set1_pd(Math::MathTraits<double>::S3),
		_mm256_set1_pd(Math::MathTraits<double>::S4),
		_mm256_set1_pd(Math::MathTraits<double>::S5),
		_mm256_set1_pd(Math::MathTraits<double>::S6),
		_mm256_set1_pd(Math::MathTraits<double>::S7),
		_mm256_set1_pd(Math::MathTraits<double>::S8)
	};

	static const __m256d cos_coeffs_d[] = {
		_mm256_set1_pd(Math::MathTraits<double>::C1),
		_mm256_set1_pd(Math::MathTraits<double>::C2),
		_mm256_set1_pd(Math::MathTraits<double>::C3),
		_mm256_set1_pd(Math::MathTraits<double>::C4),
		_mm256_set1_pd(Math::MathTraits<double>::C5),
		_mm256_set1_pd(Math::MathTraits<double>::C6),
		_mm256_set1_pd(Math::MathTraits<double>::C7),
		_mm256_set1_pd(Math::MathTraits<double>::C8)
	};

	static const __m256d atan_coeffs_d[] = {
		_mm256_set1_pd(Math::MathTraits<double>::A1),
		_mm256_set1_pd(Math::MathTraits<double>::A2),
		_mm256_set1_pd(Math::MathTraits<double>::A3),
		_mm256_set1_pd(Math::MathTraits<double>::A4),
		_mm256_set1_pd(Math::MathTraits<double>::A5),
		_mm256_set1_pd(Math::MathTraits<double>::A6),
		_mm256_set1_pd(Math::MathTraits<double>::A7),
		_mm256_set1_pd(Math::MathTraits<double>::A8)
	};

	INLINE __m128 sin(__m128 x) {
		using M = Math::MathTraits<float>;
		const __m128 TWO_PI = _mm_set1_ps(M::TWO_PI);
		const __m128 PI = _mm_set1_ps(M::PI);
		const __m128 NEG_PI = _mm_set1_ps(-M::PI);
		const __m128 EPSILON = _mm_set1_ps(M::EPSILON);

		// Range reduction x to [-PI, PI]
		x = mod(x, TWO_PI);
		__m128 gt_pi = _mm_cmpgt_ps(x, PI);
		__m128 lt_npi = _mm_cmplt_ps(x, NEG_PI);
		x = _mm_blendv_ps(x, _mm_sub_ps(x, TWO_PI), gt_pi);
		x = _mm_blendv_ps(x, _mm_add_ps(x, TWO_PI), lt_npi);

		// x small enough? Skip higher order terms
		__m128 abs_x = abs_ps(x);
		__m128 near_zero_mask = _mm_cmplt_ps(abs_x, EPSILON);
		__m128 result_linear = x;

		// Polynomial approximation
		__m128 x2 = _mm_mul_ps(x, x);
		__m128 x4 = _mm_mul_ps(x2, x2);

		__m128 t0 = fmadd(sin_coeffs[7], x, sin_coeffs[6]);
		__m128 t1 = fmadd(sin_coeffs[5], x, sin_coeffs[4]);
		__m128 t2 = fmadd(sin_coeffs[3], x, sin_coeffs[2]);
		__m128 t3 = fmadd(sin_coeffs[1], x, sin_coeffs[0]);

		__m128 p0 = fmadd(t0, x2, t1);
		__m128 p1 = fmadd(t2, x2, t3);
		__m128 poly = fmadd(p0, x4, p1);
		__m128 poly_result = _mm_mul_ps(x, poly);

		// Use blend to return x directly for small inputs
		return _mm_blendv_ps(poly_result, result_linear, near_zero_mask);
	}

	INLINE __m256d sin(__m256d x) {
		using M = Math::MathTraits<double>;
		const __m256d TWO_PI = _mm256_set1_pd(M::TWO_PI);
		const __m256d PI = _mm256_set1_pd(M::PI);
		const __m256d NEG_PI = _mm256_set1_pd(-M::PI);
		const __m256d EPSILON = _mm256_set1_pd(M::EPSILON);

		// Range reduction x to [-PI, PI]
		x = mod(x, TWO_PI);
		__m256d gt_pi = _mm256_cmp_pd(x, PI, _CMP_GT_OQ);
		__m256d lt_npi = _mm256_cmp_pd(x, NEG_PI, _CMP_LT_OQ);
		x = _mm256_blendv_pd(x, _mm256_sub_pd(x, TWO_PI), gt_pi);
		x = _mm256_blendv_pd(x, _mm256_add_pd(x, TWO_PI), lt_npi);

		// x small enough? Skip higher order terms
		__m256d abs_x = abs_pd(x);
		__m256d near_zero_mask = _mm256_cmp_pd(abs_x, EPSILON, _CMP_LT_OQ);
		__m256d result_linear = x;

		// Polynomial approximation
		__m256d x2 = _mm256_mul_pd(x, x);
		__m256d x4 = _mm256_mul_pd(x2, x2);

		__m256d t0 = _mm256_fmadd_pd(sin_coeffs_d[7], x, sin_coeffs_d[6]);
		__m256d t1 = _mm256_fmadd_pd(sin_coeffs_d[5], x, sin_coeffs_d[4]);
		__m256d t2 = _mm256_fmadd_pd(sin_coeffs_d[3], x, sin_coeffs_d[2]);
		__m256d t3 = _mm256_fmadd_pd(sin_coeffs_d[1], x, sin_coeffs_d[0]);

		__m256d p0 = _mm256_fmadd_pd(t0, x2, t1);
		__m256d p1 = _mm256_fmadd_pd(t2, x2, t3);
		__m256d poly = _mm256_fmadd_pd(p0, x4, p1);
		__m256d poly_result = _mm256_mul_pd(x, poly);

		// Use blend to return x directly for small inputs
		return _mm256_blendv_pd(poly_result, result_linear, near_zero_mask);
	}

	INLINE __m128 cos(__m128 x) {
		using M = Math::MathTraits<float>;
		const __m128 TWO_PI = _mm_set1_ps(M::TWO_PI);
		const __m128 PI = _mm_set1_ps(M::PI);
		const __m128 NEG_PI = _mm_set1_ps(-M::PI);
		const __m128 EPSILON = _mm_set1_ps(M::EPSILON);

		// Range reduce x to [-PI, PI]
		x = mod(x, TWO_PI);
		__m128 gt_pi = _mm_cmpgt_ps(x, PI);
		__m128 lt_npi = _mm_cmplt_ps(x, NEG_PI);
		x = _mm_blendv_ps(x, _mm_sub_ps(x, TWO_PI), gt_pi);
		x = _mm_blendv_ps(x, _mm_add_ps(x, TWO_PI), lt_npi);

		// cos(x) = cos(-x), so use abs(x)
		x = abs_ps(x);

		// Use cosine's even-powered Taylor expansion:
		__m128 x2 = _mm_mul_ps(x, x);
		__m128 x4 = _mm_mul_ps(x2, x2);

		__m128 t0 = fmadd(cos_coeffs[7], x2, cos_coeffs[6]);
		__m128 t1 = fmadd(cos_coeffs[5], x2, cos_coeffs[4]);
		__m128 t2 = fmadd(cos_coeffs[3], x2, cos_coeffs[2]);
		__m128 t3 = fmadd(cos_coeffs[1], x2, cos_coeffs[0]);

		__m128 p0 = fmadd(t0, x4, t1);
		__m128 p1 = fmadd(t2, x4, t3);
		__m128 result = fmadd(p0, _mm_mul_ps(x4, x4), p1);

		// Short-circuit near x=0
		__m128 near_zero = _mm_cmplt_ps(x, EPSILON);
		return _mm_blendv_ps(result, _mm_set1_ps(1.0f), near_zero);
	}

	INLINE __m256d cos(__m256d x) {
		using M = Math::MathTraits<double>;
		const __m256d TWO_PI = _mm256_set1_pd(M::TWO_PI);
		const __m256d PI = _mm256_set1_pd(M::PI);
		const __m256d NEG_PI = _mm256_set1_pd(-M::PI);
		const __m256d EPSILON = _mm256_set1_pd(M::EPSILON);

		// Range reduction x to [-PI, PI]
		x = mod(x, TWO_PI);
		__m256d gt_pi = _mm256_cmp_pd(x, PI, _CMP_GT_OQ);
		__m256d lt_npi = _mm256_cmp_pd(x, NEG_PI, _CMP_LT_OQ);
		x = _mm256_blendv_pd(x, _mm256_sub_pd(x, TWO_PI), gt_pi);
		x = _mm256_blendv_pd(x, _mm256_add_pd(x, TWO_PI), lt_npi);

		// cos(x) = cos(-x), so use abs(x)
		x = abs_pd(x);

		// Use cosine's even-powered Taylor expansion:
		__m256d x2 = _mm256_mul_pd(x, x);
		__m256d x4 = _mm256_mul_pd(x2, x2);

		__m256d t0 = _mm256_fmadd_pd(cos_coeffs_d[7], x, cos_coeffs_d[6]);
		__m256d t1 = _mm256_fmadd_pd(cos_coeffs_d[5], x, cos_coeffs_d[4]);
		__m256d t2 = _mm256_fmadd_pd(cos_coeffs_d[3], x, cos_coeffs_d[2]);
		__m256d t3 = _mm256_fmadd_pd(cos_coeffs_d[1], x, cos_coeffs_d[0]);

		__m256d p0 = _mm256_fmadd_pd(t0, x2, t1);
		__m256d p1 = _mm256_fmadd_pd(t2, x2, t3);
		__m256d result = _mm256_fmadd_pd(p0, x4, p1);

		// Short-circuit near x=0
		__m256d near_zero = _mm256_cmp_pd(x, EPSILON, _CMP_LT_OQ);
		return _mm256_blendv_pd(result, _mm256_set1_pd(1.0), near_zero);
	}

	INLINE __m128 tan(__m128 x) {
		return _mm_div_ps(sin(x), cos(x));
	}

	INLINE __m256d tan(__m256d x) {
		return _mm256_div_pd(sin(x), cos(x));
	}

	INLINE __m128 sec(__m128 x) {
		return _mm_div_ps(_mm_set1_ps(1.0f), cos(x));
	}

	INLINE __m256d sec(__m256d x) {
		return _mm256_div_pd(_mm256_set1_pd(1.0), cos(x));
	}

	INLINE __m128 csc(__m128 x) {
		return _mm_div_ps(_mm_set1_ps(1.0f), sin(x));
	}

	INLINE __m256d csc(__m256d x) {
		return _mm256_div_pd(_mm256_set1_pd(1.0), sin(x));
	}

	INLINE __m128 cot(__m128 x) {
		return _mm_div_ps(_mm_set1_ps(1.0f), tan(x));
	}

	INLINE __m256d cot(__m256d x) {
		return _mm256_div_pd(_mm256_set1_pd(1.0), tan(x));
	}

	INLINE __m128 asin(__m128 x) {
		__m128 sqrt = _mm_sqrt_ps(_mm_sub_ps(_mm_set1_ps(1.0f), _mm_mul_ps(x, x)));
		return atan(_mm_div_ps(x, sqrt));
	}

	INLINE __m256d asin(__m256d x) {
		__m256d sqrt = _mm256_sqrt_pd(_mm256_sub_pd(_mm256_set1_pd(1.0), _mm256_mul_pd(x, x)));
		return atan(_mm256_div_pd(x, sqrt));
	}

	INLINE __m128 acos(__m128 x) {
		const __m128 HALF_PI = _mm_set1_ps(Math::MathTraits<float>::HALF_PI);
		return _mm_sub_ps(HALF_PI, asin(x));
	}

	INLINE __m256d acos(__m256d x) {
		const __m256d HALF_PI = _mm256_set1_pd(Math::MathTraits<double>::HALF_PI);
		return _mm256_sub_pd(HALF_PI, asin(x));
	}

	INLINE __m128 atan(__m128 x) {
		using M = Math::MathTraits<float>;

		__m128 abs_x = abs_ps(x);
		__m128 one = _mm_set1_ps(1.0f);
		__m128 inv_x = _mm_div_ps(one, x);

		__m128 swap_mask = _mm_cmpgt_ps(abs_x, one);
		__m128 z = _mm_blendv_ps(x, inv_x, swap_mask);

		__m128 z2 = _mm_mul_ps(z, z);
		__m128 z4 = _mm_mul_ps(z2, z2);

		__m128 t0 = fmadd(atan_coeffs[7], z2, atan_coeffs[6]);
		__m128 t1 = fmadd(atan_coeffs[5], z2, atan_coeffs[4]);
		__m128 t2 = fmadd(atan_coeffs[3], z2, atan_coeffs[2]);
		__m128 t3 = fmadd(atan_coeffs[1], z2, atan_coeffs[0]);

		__m128 p0 = fmadd(t0, z2, t1);
		__m128 p1 = fmadd(t2, z2, t3);
		__m128 poly = fmadd(p0, z4, p1);

		__m128 result = fmadd(poly, z, z);

		const __m128 HALF_PI = _mm_set1_ps(M::HALF_PI);
		return _mm_blendv_ps(result, _mm_sub_ps(HALF_PI, result), swap_mask);;
	}

	INLINE __m256d atan(__m256d x) {
		using M = Math::MathTraits<double>;

		__m256d abs_x = abs_pd(x);
		__m256d one = _mm256_set1_pd(1.0f);
		__m256d inv_x = _mm256_div_pd(one, x);

		__m256d swap_mask = _mm256_cmp_pd(abs_x, one, _CMP_GT_OQ);
		__m256d z = _mm256_blendv_pd(x, inv_x, swap_mask);

		__m256d z2 = _mm256_mul_pd(z, z);
		__m256d z4 = _mm256_mul_pd(z2, z2);

		__m256d t0 = _mm256_fmadd_pd(atan_coeffs_d[7], z2, atan_coeffs_d[6]);
		__m256d t1 = _mm256_fmadd_pd(atan_coeffs_d[5], z2, atan_coeffs_d[4]);
		__m256d t2 = _mm256_fmadd_pd(atan_coeffs_d[3], z2, atan_coeffs_d[2]);
		__m256d t3 = _mm256_fmadd_pd(atan_coeffs_d[1], z2, atan_coeffs_d[0]);

		__m256d p0 = _mm256_fmadd_pd(t0, z2, t1);
		__m256d p1 = _mm256_fmadd_pd(t2, z2, t3);
		__m256d poly = _mm256_fmadd_pd(p0, z4, p1);

		__m256d result = _mm256_fmadd_pd(poly, z, z);

		const __m256d HALF_PI = _mm256_set1_pd(M::HALF_PI);
		return _mm256_blendv_pd(result, _mm256_sub_pd(HALF_PI, result), swap_mask);
	}

	INLINE __m128 atan2(__m128 y, __m128 x) {
		const __m128 pi = _mm_set1_ps(Math::MathTraits<float>::PI);
		const __m128 pi_2 = _mm_set1_ps(Math::MathTraits<float>::HALF_PI);
		const __m128 zero = _mm_setzero_ps();

		__m128 abs_x = abs_ps(x);
		__m128 abs_y = abs_ps(y);

		__m128 atan_base = atan(_mm_div_ps(abs_y, abs_x));
		__m128 result = atan_base;

		__m128 x_neg = _mm_cmplt_ps(x, zero);
		__m128 y_neg = _mm_cmplt_ps(y, zero);
		__m128 x_pos = _mm_cmpgt_ps(x, zero);

		result = _mm_blendv_ps(result, _mm_sub_ps(pi, atan_base), x_neg);
		result = _mm_blendv_ps(result, _mm_sub_ps(zero, result), y_neg);

		// handle x = 0
		__m128 x_zero = _mm_cmpeq_ps(x, zero);
		result = _mm_blendv_ps(result, pi_2, _mm_and_ps(x_zero, _mm_cmpgt_ps(y, zero)));
		result = _mm_blendv_ps(result, _mm_sub_ps(_mm_setzero_ps(), pi_2), _mm_and_ps(x_zero, y_neg));

		return result;
	}

	INLINE __m256d atan2(__m256d y, __m256d x) {
		const __m256d pi = _mm256_set1_pd(Math::MathTraits<double>::PI);
		const __m256d pi_2 = _mm256_set1_pd(Math::MathTraits<double>::HALF_PI);
		const __m256d zero = _mm256_setzero_pd();

		__m256d abs_x = abs_pd(x);
		__m256d abs_y = abs_pd(y);

		__m256d atan_base = atan(_mm256_div_pd(abs_y, abs_x));
		__m256d result = atan_base;

		__m256d x_neg = _mm256_cmp_pd(x, zero, _CMP_LT_OQ);
		__m256d y_neg = _mm256_cmp_pd(y, zero, _CMP_LT_OQ);
		__m256d x_pos = _mm256_cmp_pd(x, zero, _CMP_GT_OQ);

		result = _mm256_blendv_pd(result, _mm256_sub_pd(pi, atan_base), x_neg);
		result = _mm256_blendv_pd(result, _mm256_sub_pd(zero, result), y_neg);

		// handle x = 0
		__m256d x_zero = _mm256_cmp_pd(x, zero, _CMP_EQ_OQ);
		result = _mm256_blendv_pd(result, pi_2, _mm256_and_pd(x_zero, _mm256_cmp_pd(y, zero, _CMP_GT_OQ)));
		result = _mm256_blendv_pd(result, _mm256_sub_pd(_mm256_setzero_pd(), pi_2), _mm256_and_pd(x_zero, y_neg));

		return result;
	}
}
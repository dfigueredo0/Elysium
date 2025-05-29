#pragma once

#include "Elysium/Core.h"

#include "Common.h"

#include "../Matrix.hpp"

namespace SIMD {
	INLINE Math::Matrix<float, 4, 4> mat_mul(const Math::Matrix<float, 4, 4>& u, const Math::Matrix<float, 4, 4>& b) {

	}

	INLINE Math::Matrix<double, 4, 4> mat_mul(const Math::Matrix<double, 4, 4>& u, const Math::Matrix<double, 4, 4>& b) {

	}

	INLINE Math::Matrix<float, 3, 3> mat_mul(const Math::Matrix<float, 3, 3>& u, const Math::Matrix<float, 3, 3>& b) {

	}

	INLINE Math::Matrix<double, 3, 3> mat_mul(const Math::Matrix<double, 3, 3>& u, const Math::Matrix<double, 3, 3>& b) {

	}

	INLINE Math::Matrix<float, 4, 4> mat_transpose(const Math::Matrix<float, 4, 4>& m) {

	}

	INLINE Math::Matrix<double, 4, 4> mat_transpose(const Math::Matrix<double, 4, 4>& m) {

	}

	INLINE Math::Matrix<float, 4, 4> mat_inverse(const Math::Matrix<float, 4, 4>& m) {

	}

	INLINE Math::Matrix<double, 4, 4> mat_inverse(const Math::Matrix<double, 4, 4>& m) {

	}
	
	INLINE Math::Matrix<float, 3, 3> mat_inverse(const Math::Matrix<float, 3, 3>& m) {

	}

	INLINE Math::Matrix<double, 3, 3> mat_inverse(const Math::Matrix<double, 3, 3>& m) {

	}

	INLINE float mat_determinant(const Math::Matrix<float, 3, 3>& m) {

	}

	INLINE float mat_determinant(const Math::Matrix<float, 4, 4>& m) {

	}

	INLINE double mat_determinant(const Math::Matrix<double, 3, 3>& m) {

	}

	INLINE double mat_determinant(const Math::Matrix<double, 4, 4 > &m) {

	}

	INLINE __m128 mat_mul_vec(const Math::Matrix<float, 4, 4>& m, __m128 v) {

	}

	INLINE __m256d mat_mul_vec(const Math::Matrix<double, 4, 4>& m, __m256d v) {

	}

	INLINE Math::Matrix<float, 4, 4> mat_scale(__m128 scale) {

	}


	INLINE Math::Matrix<double, 4, 4> mat_scale(__m256 scale) {

	}

	INLINE Math::Matrix<float, 4, 4> mat_translate(__m128 xyz) {

	}

	INLINE Math::Matrix<float, 4, 4> mat_rotate(float angle, __m128 axis) {

	}

	INLINE Math::Matrix<double, 4, 4> mat_rotate(double angle, __m256 axis) {

	}

	INLINE Math::Matrix<double, 4, 4> mat_translate(__m256 xyz) {

	}
}
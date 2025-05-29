#pragma once

#include "Elysium/Core.h"

#include "Functions.hpp"
#include "Vec.hpp"
#include "Quaternion.hpp"

namespace Math {
	INLINE float lerp(float a, float b, float t) {
		return a + t * (b - a);
	}

	INLINE double lerp(double a, double b, double t) {
		return a + t * (b - a);
	}


	template<typename T>
	INLINE vec<T, 3> lerp(const vec<T, 3>& a, const vec<T, 3>& b, T t) {
		return a * (1 - t) + b * t;
	}

	template<typename T>
	INLINE quat<T> lerp(const quat<T>& a, const quat<T>& b, T t) {
		return a * (1 - t) + b * t;
	}

	INLINE float inverseLerp(float a, float b, float value) {
		if (a == b) return 0.0f;
		return (value - a) / (b - a);
	}

	INLINE double inverseLerp(double a, double b, double value) {
		if (a == b) return 0.0;
		return (value - a) / (b - a);
	}

	INLINE float step(float x) {
		return x < 0.0f ? 0.0f : 1.0f;
	}

	INLINE double step(double x) {
		return x < 0.0 ? 0.0 : 1.0;
	}

	INLINE float smoothStep(float edge, float edge1, float t) {
		float x = clamp((t - edge) / (edge1 - edge), 0.0f, 1.0f);
		return x * x * (3.0f - 2.0f * x);
	}

	INLINE double smoothStep(double edge, double edge1, double t) {
		double x = clamp((t - edge) / (edge1 - edge), 0.0, 1.0);
		return x * x * (3.0 - 2.0 * x);
	}


	INLINE float slerp(float a, float b, float t) {
		using M = MathTraits<float>;
		float dot = cos(t * M::PI);
		float theta = a + (b - a) * t;
		return sin((1.0f - t) * theta) / sin(theta) * a +
			sin(t * theta) / sin(theta) * b;
	}

	INLINE double slerp(double a, double b, double t) {
		using M = MathTraits<double>;
		double dot = cos(t * M::PI);
		double theta = a + (b - a) * t;
		return sin((1.0 - t) * theta) / sin(theta) * a +
			sin(t * theta) / sin(theta) * b;
	}

	template<typename T>
	INLINE vec<T, 3> slerp(vec<T, 3> a, vec<T, 3> b, T t) {
		using M = MathTraits<T>;
		Math::vec3Normalize(&a);
		Math::vec3Normalize(&b);

		T dot = Math::vec3Dot(a, b);
		dot = Math::clamp(dot, static_cast<T>(-1), static_cast<T>(1));

		if (dot > static_cast<T>(0.9995)) {
			return Math::vec3Normalized(Math::lerp(a, b, t));
		}

		T theta = Math::acos(dot);
		T sinTheta = Math::sin(theta);

		T w1 = Math::sin((1 - t) * theta) / sinTheta;
		T w2 = Math::sin(t * theta) / sinTheta;

		return a * w1 + b * w2;
	}

	/**
	*
	*	@param q Starting quaternion value
	*	@param r Ending quaternion value
	*	@param t Interpolation ratio. Value range is [0, 1].
	*/
	template<typename T>
	INLINE quat<T> slerp(quat<T> q, quat<T> r, T t) {
		q = quatNormalize(q);
		r = quatNormalize(r);
		quat<T> result;
		T cosHalfTheta = quatDot(q, r);

		if (cosHalfTheta < 0.0f) {
			r.x = -r.x;
			r.y = -r.y;
			r.z = -r.z;
			r.w = -r.w;
			cosHalfTheta = -cosHalfTheta;
		}

		const T DOT_THRESHOLD = 0.9995f;
		if (cosHalfTheta > DOT_THRESHOLD) {
			// Linear interpolation + normalize
			for (int i = 0; i < 4; ++i)
				result.elements[i] = q.elements[i] + (r.elements[i] - q.elements[i]) * t;
			return quatNormalize(result);
		}


		T theta = Math::acos(cosHalfTheta);
		T sinTheta = Math::sin(theta);

		T s0 = Math::sin((1 - t) * theta) / sinTheta;
		T s1 = Math::sin(t * theta) / sinTheta;

		for (int i = 0; i < 4; ++i)
			result.elements[i] = q.elements[i] * s0 + r.elements[i] * s1;

		return quatNormalize(result);
	}

	template<typename T, int N>
	INLINE Matrix<T, N, N> slerp(const Matrix<T, N, N>& A, const Matrix<T, N, N>& B, T t) {
		using M = MathTraits<T>;

		// Compute rotation difference
		Matrix<T, N, N> R = Math::getInverse(A) * B;

		// Convert to axis-angle
		vec<T, 3> axis;
		T angle = 0;

		// For 3x3 only
		if constexpr (N == 3) {
			T trace = R(0, 0) + R(1, 1) + R(2, 2);
			angle = Math::acos(Math::clamp((trace - 1) / 2, static_cast<T>(-1), static_cast<T>(1)));

			axis.x = R(2, 1) - R(1, 2);
			axis.y = R(0, 2) - R(2, 0);
			axis.z = R(1, 0) - R(0, 1);
			Math::vec3Normalize(&axis);
		}
		else {
			// For 4x4: Extract upper-left 3x3 and do same
			Matrix<T, 3, 3> RA, RB;
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j) {
					RA(i, j) = A(i, j);
					RB(i, j) = B(i, j);
				}

			Matrix<T, 3, 3> R3 = Math::getInverse(RA) * RB;
			T trace = R3(0, 0) + R3(1, 1) + R3(2, 2);
			angle = Math::acos(Math::clamp((trace - 1) / 2, static_cast<T>(-1), static_cast<T>(1)));

			axis.x = R3(2, 1) - R3(1, 2);
			axis.y = R3(0, 2) - R3(2, 0);
			axis.z = R3(1, 0) - R3(0, 1);
			Math::vec3Normalize(&axis);
		}

		// Interpolated rotation matrix = A * rotation_matrix(axis, t * angle)
		Matrix<T, N, N> R_interp;
		if constexpr (N == 3) {
			T c = Math::cos(t * angle);
			T s = Math::sin(t * angle);
			T one_c = static_cast<T>(1) - c;

			const T x = axis.x, y = axis.y, z = axis.z;
			R_interp = Matrix<T, 3, 3>::identity();

			R_interp(0, 0) = c + x * x * one_c;
			R_interp(0, 1) = x * y * one_c - z * s;
			R_interp(0, 2) = x * z * one_c + y * s;

			R_interp(1, 0) = y * x * one_c + z * s;
			R_interp(1, 1) = c + y * y * one_c;
			R_interp(1, 2) = y * z * one_c - x * s;

			R_interp(2, 0) = z * x * one_c - y * s;
			R_interp(2, 1) = z * y * one_c + x * s;
			R_interp(2, 2) = c + z * z * one_c;

			return A * R_interp;
		}
		else {
			// Convert 3x3 rotation to 4x4 rotation matrix
			Matrix<T, 4, 4> R4 = Matrix<T, 4, 4>::identity();
			T c = Math::cos(t * angle);
			T s = Math::sin(t * angle);
			T one_c = static_cast<T>(1) - c;

			const T x = axis.x, y = axis.y, z = axis.z;

			R4(0, 0) = c + x * x * one_c;
			R4(0, 1) = x * y * one_c - z * s;
			R4(0, 2) = x * z * one_c + y * s;

			R4(1, 0) = y * x * one_c + z * s;
			R4(1, 1) = c + y * y * one_c;
			R4(1, 2) = y * z * one_c - x * s;

			R4(2, 0) = z * x * one_c - y * s;
			R4(2, 1) = z * y * one_c + x * s;
			R4(2, 2) = c + z * z * one_c;

			return A * R4;
		}
	}
}
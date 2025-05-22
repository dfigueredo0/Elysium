#pragma once

#include "Elysium/Core.h"
#include "Functions.hpp"
#include "Matrix.hpp"
#include "Vec.hpp"

namespace Math {
	template<typename T>
	struct alignas(16) quat {
		union {
			struct { T x, y, z, w; };
			T elements[4];
			vec<T, 4> vec;
		};

		constexpr quat() : x(0), y(0), z(0), w(1) {}
		quat(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
			elements[0] = x; elements[1] = y; elements[2] = z; elements[3] = w;
		}
	};
	
	template<typename T>
	INLINE quat<T> quatIdentity() {
		return quat(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template<typename T>
	INLINE T quatNormal(quat<T> q) {
		return Math::sqrt(
			q.x * q.x +
			q.y * q.y +
			q.z * q.z +
			q.w * q.w
		);
	}

	template<typename T>
	INLINE quat<T> quatNormalize(quat<T> q) {
		T norm = quatNormal(q);
		if (norm <= EPSILON) return quat<T>(); // or identity
		return quat<T>(q.x / norm, q.y / norm, q.z / norm, q.w / norm);
	}

	template<typename T>
	INLINE quat<T> quatConjugate(quat<T> q) {
		return quat(-q.x, -q.y, -q.z, q.w);
	}

	template<typename T>
	INLINE quat<T> quatInverse(quat<T> q) {
		return quatNormalize(quatConjugate(q));
	}

	template<typename T>
	INLINE quat<T> quatMul(quat<T> q, quat<T> r) {
		quat<T> t;

		t.x = r.w * q.x + r.x * q.w - r.y * q.z + r.z * q.y;
		t.y = r.w * q.y + r.x * q.z + r.y * q.w - r.z * q.x;
		t.z = r.w * q.z - r.x * q.y + r.y * q.x + r.z * q.w;
		t.w = r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z;

		return t;
	}

	template<typename T>
	INLINE T quatDot(quat<T> q, quat<T> r) {
		return q.x * r.x + q.y * r.y + q.z * r.z + q.w * r.w;
	}

	template<typename T>
	INLINE Matrix<T, 4, 4> quatToMat4(quat<T> q) {
		Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
		quat<T> n = quatNormalize(q);

		T x = n.x, y = n.y, z = n.z, w = n.w;
		T xx = x * x, yy = y * y, zz = z * z;
		T xy = x * y, xz = x * z, yz = y * z;
		T wx = w * x, wy = w * y, wz = w * z;


		mat.data[0] = 1.0f - 2.0f * (yy + zz);
		mat.data[1] = 2.0f * (xy - wz);
		mat.data[2] = 2.0f * (xz + wy);

		mat.data[4] = 2.0f * (xy + wz);
		mat.data[5] = 1.0f - 2.0f * (xx + zz);
		mat.data[6] = 2.0f * (yz - wx);

		mat.data[8] = 2.0f * (xz - wy);
		mat.data[9] = 2.0f * (yz + wx);
		mat.data[10] = 1.0f - 2.0f * (xx + yy);

		return mat;
	}

	template<typename T>
	INLINE Matrix<T, 4, 4> quatToRotMatrix(quat<T> q, vec<T, 3> center) {
		q = quatNormalize(q);

		T x = q.x, y = q.y, z = q.z, w = q.w;
		T xx = x * x, yy = y * y, zz = z * z;
		T xy = x * y, xz = x * z, yz = y * z;
		T wx = w * x, wy = w * y, wz = w * z;

		Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();

		mat(0, 0) = 1.0f - 2.0f * (yy + zz);
		mat(0, 1) = 2.0f * (xy - wz);
		mat(0, 2) = 2.0f * (xz + wy);
		mat(0, 3) = 0.0f;

		mat(1, 0) = 2.0f * (xy + wz);
		mat(1, 1) = 1.0f - 2.0f * (xx + zz);
		mat(1, 2) = 2.0f * (yz - wx);
		mat(1, 3) = 0.0f;

		mat(2, 0) = 2.0f * (xz - wy);
		mat(2, 1) = 2.0f * (yz + wx);
		mat(2, 2) = 1.0f - 2.0f * (xx + yy);
		mat(2, 3) = 0.0f;

		// Compute translation so that the rotation is centered around `center`
		T tx = center.x - (mat(0, 0) * center.x + mat(0, 1) * center.y + mat(0, 2) * center.z);
		T ty = center.y - (mat(1, 0) * center.x + mat(1, 1) * center.y + mat(1, 2) * center.z);
		T tz = center.z - (mat(2, 0) * center.x + mat(2, 1) * center.y + mat(2, 2) * center.z);

		mat(3, 0) = tx;
		mat(3, 1) = ty;
		mat(3, 2) = tz;
		mat(3, 3) = 1.0f;

		return mat;
	}

	template<typename T>
	INLINE quat<T> quatFromAxisAngle(vec<T, 3> axis, T angle, bool normalize) {
		const T half_angle = 0.5f * angle;

		T s = sin(half_angle);
		T c = cos(half_angle);

		quat<T> q = quat(s * axis.x, s * axis.y, s * axis.z, c);

		if (normalize) {
			return quatNormalize(q);
		}

		return q;
	}

	/**
	*
	*	@param q Starting quaternion value
	*	@param r Ending quaternion value
	*	@param t Interpolation ratio. Value range is [0, 1].
	*/
	template<typename T>
	INLINE quat<T> quatSlerp(quat<T> q, quat<T> r, T t) {
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

	using quatf = quat<float>;
	using quatd = quat<double>;
}
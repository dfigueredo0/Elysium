#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"

namespace Math {
	template<typename T>
	INLINE vec<T, 4> vec4Create(T x, T y, T z, T w) {
		return vec<T, 4>(x, y, z, w);
	}

	template<typename T>
	INLINE vec<T, 3> vec4ToVec3(vec<T, 4> u) {
		return vec<T, 3>(u.x, u.y, u.z);
	}

	template<typename T>
	INLINE vec<T, 4> vec4FromVec3(vec<T, 3> u, T w) {
		return vec<T, 4>(u.x, u.y, u.z, w);
	}

	template<typename T>
	INLINE vec<T, 4> vec4Zero() { return vec<T, 4>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

	template<typename T>
	INLINE vec<T, 4> vec4MulMat4(Matrix<T, 4, 4> m, vec<T, 4> v) {
		return vec<T, 4>(
			v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[8] + v.w * m.data[12],
			v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[9] + v.w * m.data[13],
			v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[10] + v.w * m.data[14],
			v.x * m.data[3] + v.y * m.data[7] + v.z * m.data[11] + v.w * m.data[15]
		);
	}

	template<typename T>
	INLINE T vec4Dot(vec<T, 4> u, vec<T, 4> v) {
		T result = 0;
		for (int i = 0; i < 4; ++i) {
			result += u.elements[i] * v.elements[i];
		}
		return result;
	}

	INLINE float vec4DotF32(float x, float y, float z, float w, float x1, float y1, float z1, float w1) {
		float result = 0.0f;
		result =
			x * x1 +
			y * y1 +
			z * z1 +
			w * w1;
		return result;
	}

	template<typename T>
	INLINE T vec4SquaredLength(vec<T, 4> u) {
		return u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w;
	}

	template<typename T>
	INLINE T vec4Length(vec<T, 4> u) {
		return sqrt(vec4SquaredLength(u));
	}

	template<typename T>
	INLINE void vec4Normalize(vec<T, 4>* v) {
		using M = MathTraits<T>;

		const T len = vec4Length(*v);
		v->x = (len > M::EPSILON) ? v->x / len : 0;
		v->y = (len > M::EPSILON) ? v->y / len : 0;
		v->z = (len > M::EPSILON) ? v->z / len : 0;
		v->w = (len > M::EPSILON) ? v->w / len : 0;
	}

	template<typename T>
	INLINE vec<T, 4> vec4Normalized(vec<T, 4> v) {
		vec4Normalize(&v);
		return v;
	}

	using vec4 = vec<float, 4>;
	using vec4d = vec<double, 4>;
}

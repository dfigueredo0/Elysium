#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"
#include "Vec3.hpp"

namespace Math {
	struct alignas(16) vec4 {
		union {
			__m128 data;
			struct {
				union { float x, r, s; };
				union { float y, g, r; };
				union { float z, b, p; };
				union { float w, a, q; };
			};
			float elements[4];
		};
#if SIMD_LEVEL_AVX512
		INLINE vec4() : data(_mm_setzero_ps()) {}
		INLINE vec4(float x, float y, float z, float w) : data(_mm_set_ps(w, z, y, x)) {}
#endif
		INLINE vec4() : x(0), y(0), z(0), w(0) {
			elements[0] = x;
			elements[1] = y;
			elements[2] = z;
			elements[3] = w;
		}

		INLINE vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {
			elements[0] = x;
			elements[1] = y;
			elements[2] = z;
			elements[3] = w;
		}
	};

	INLINE vec4 vec4Create(float x, float y, float z, float w) {
		return vec4(x, y, z, w);
	}

	INLINE vec3 vec4ToVec3(vec4 u) {
		return vec3(u.x, u.y, u.z);
	}

	INLINE vec4 vec4FromVec3(vec3 u, float w) {
		return vec4(u.x, u.y, u.z, w);
	}

	INLINE vec4 vec4Zero() { return vec4(0.0f, 0.0f, 0.0f, 0.0f); }

	INLINE vec4 vec4Add(vec4 u, vec4 v) {
		vec4 result;
		for (int i = 0; i < 4; ++i) {
			result.elements[i] = u.elements[i] + v.elements[i];
		}
		return result;
	}

	INLINE vec4 vec4Sub(vec4 u, vec4 v) {
		vec4 result;
		for (int i = 0; i < 4; ++i) {
			result.elements[i] = u.elements[i] - v.elements[i];
		}
		return result;
	}

	INLINE vec4 vec4Mul(vec4 u, vec4 v) {
		vec4 result;
		for (int i = 0; i < 4; ++i) {
			result.elements[i] = u.elements[i] * v.elements[i];
		}
		return result;
	}

	INLINE vec4 vec4Div(vec4 u, vec4 v) {
		vec4 result;
		for (int i = 0; i < 4; ++i) {
			result.elements[i] = (v.elements[i] > 0) ? u.elements[i] / v.elements[i] : 0.0f;
		}
		return result;
	}

	INLINE float vec4Dot(vec4 u, vec4 v) {
		float result;
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

	INLINE float vec4SquaredLength(vec4 u) {
		return u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w;
	}

	INLINE float vec4Length(vec4 u) {
		return fsqrt(vec4SquaredLength(u));
	}

	INLINE void vec4Normalize(vec4* vector) {
		const float len = vec4Length(*vector);
		vector->x = (len > EPSILON) ? vector->x / len : 0;
		vector->y = (len > EPSILON) ? vector->y / len : 0;
		vector->z = (len > EPSILON) ? vector->z / len : 0;
		vector->w = (len > EPSILON) ? vector->w / len : 0;
	}

	INLINE vec4 vec4Normalized(vec4 vector) {
		vec4Normalize(&vector);
		return vector;
	}
}
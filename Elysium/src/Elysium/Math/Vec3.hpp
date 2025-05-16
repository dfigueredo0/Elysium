#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"

namespace Math {
	struct alignas(16) vec3 {
		union {
			__m128 data;
			struct {
				union { float x, r, s, u; };
				union { float y, g, t, v; };
				union { float z, b, p, w; };
				float _padding[1];
			};
			float elements[4];
		};

		INLINE vec3() : data(_mm_setzero_ps()) {}
		INLINE vec3(float x, float y, float z) : data(_mm_set_ps(0.0f, z, y, x)) {}
	};

	INLINE vec3 vec3Create(float x, float y, float z) {
		return vec3(x, y, z);
	}

    INLINE vec3 vec3FromVec4(vec4 u) {
        return vec3(u.x, u.y, u.z);
    }


	INLINE vec3 vec3Zero() { return vec3(0.0f, 0.0f, 0.0f); }
	INLINE vec3 vec3Up() { return vec3(0.0f, 1.0f, 0.0f); }
	INLINE vec3 vec3Down() { return vec3(0.0f, -1.0f, 0.0f); }
	INLINE vec3 vec3Left() { return vec3(-1.0f, 0.0f, 0.0f); }
	INLINE vec3 vec3Right() { return vec3(1.0f, 0.0f, 0.0f); }
	// Look into might have to be other way around but also could be dependant on LHR or RHR.
	INLINE vec3 vec3Forward() { return vec3(0.0f, 0.0f, 1.0f); }
	INLINE vec3 vec3Backward() { return vec3(0.0f, 0.0f, -1.0f); }

    INLINE vec3 vec3Add(vec3 u, vec3 v) {
        return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
    }

    INLINE vec3 vec3Sub(vec3 u, vec3 v) {
        return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
    }

    INLINE vec3 vec3Mul(vec3 u, vec3 v) {
        return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    INLINE vec3 vec3MulScalar(vec3 u, float scalar) {
        return vec3(
            u.x * scalar,
            u.y * scalar,
            u.z * scalar
        );
    }

    INLINE vec3 vec3Div(vec3 u, vec3 v) {
        return vec3(
            v.x != 0.0f ? u.x / v.x : 0.0f,
            v.y != 0.0f ? u.y / v.y : 0.0f,
            v.z != 0.0f ? u.z / v.z : 0.0f
        );
    }

    INLINE float vec3Dot(vec3 u, vec3 v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    INLINE vec3 vec3Cross(vec3 u, vec3 v) {
        return vec3(
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y - v.x
        );
    }

    INLINE float vec3SquaredLength(vec3 vector) {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    }

    INLINE float vec3Length(vec3 vector) {
        return sqrt(vec3SquaredLength(vector));
    }

    INLINE void vec3Normalize(vec3* vector) {
        const float len = vec3Length(*vector);
        vector->x = (len > EPSILON) ? vector->x / len : 0;
        vector->y = (len > EPSILON) ? vector->y / len : 0;
        vector->z = (len > EPSILON) ? vector->z / len : 0;
    }

    INLINE vec3 vec3Normalized(vec3 vector) {
        vec3Normalize(&vector);
        return vector;
    }

    /**
    *   @brief Compares all elements of u and v and ensures the differense is less than the tolerance.
    *
    *   @param u The first vector.
    *   @param v The second vector.
    *   @param epsilon The difference tolerance.
    *   @return True if within epsilon; otherwise false.
    */
    INLINE char vec3Compare(vec3 u, vec3 v, float epsilon) {
        return (fabs(u.x - v.x) <= epsilon) && (fabs(u.y - v.y) <= epsilon) && (fabs(u.z - v.z) <= epsilon);
    }

    INLINE float vec3Distance(vec3 u, vec3 v) {
        return vec3Length(vec3Sub(u, v));
    }
}
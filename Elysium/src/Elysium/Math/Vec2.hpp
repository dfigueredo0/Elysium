#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"


//TODO: SIMD impl
namespace Math {
    struct alignas(16) vec2 {
        union {
            __m128 data;
            struct {
                union { float x, r, s, u; };
                union { float y, g, t, v; };
                float _padding[2];
            };
            float elements[4];
        };

        INLINE vec2() : data(_mm_setzero_ps()) {}
        INLINE vec2(float xVal, float yVal) : data(_mm_set_ps(0.0f, 0.0f, yVal, xVal)) {}
    };

    /**
    *   @brief Create and returns a new 2-element vector
    * 
    *   @param x The 1st element's value
    *   @param y The 2nd element's value
    *   @return A new 2-element vector.
    */
    INLINE vec2 vec2Create(float x, float y) {
        return vec2(x, y);
    }

    INLINE vec2 vec2Zero() { return vec2(0.0f, 0.0f); }
    INLINE vec2 vec2Up() { return vec2(0.0f, 1.0f); }
    INLINE vec2 vec2Down() { return vec2(0.0f, -1.0f); }
    INLINE vec2 vec2Left() { return vec2(-1.0f, 0.0f); }
    INLINE vec2 vec2Right() { return vec2(1.0f, 0.0f); }

    INLINE vec2 vec2Add(vec2 u, vec2 v) {
        return vec2(u.x + v.x, u.y + v.y);
    }

    INLINE vec2 vec2Sub(vec2 u, vec2 v) {
        return vec2(u.x - v.x, u.y - v.y);
    }

    INLINE vec2 vec2Mul(vec2 u, vec2 v) {
        return vec2(u.x * v.x, u.y * v.y);
    }

    INLINE vec2 vec2Div(vec2 u, vec2 v) {
        return vec2(
            v.x != 0.0f ? u.x / v.x : 0.0f,
            v.y != 0.0f ? u.y / v.y : 0.0f
        );
    }

    INLINE float vec2Dot(vec2 u, vec2 v) {
        return u.x * v.x + u.y * v.y;
    }

    INLINE float vec2SquaredLength(vec2 vector) {
        return vector.x * vector.x + vector.y * vector.y;
    }

    INLINE float vec2Length(vec2 vector) {
        return sqrt(vec2SquaredLength(vector));
    }

    INLINE void vec2Normalize(vec2* vector) {
        const float len = vec2Length(*vector);
        vector->x = (len > EPSILON) ? vector->x / len : 0;
        vector->y = (len > EPSILON) ? vector->y / len : 0;
    }

    INLINE vec2 vec2Normalized(vec2 vector) {
        vec2Normalize(&vector);
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
    INLINE char vec2Compare(vec2 u, vec2 v, float epsilon) {
        return (fabs(u.x - v.x) <= epsilon) && (fabs(u.y - v.y) <= epsilon);
    }

    INLINE float vec2Distance(vec2 u, vec2 v) {
        return vec2Length(vec2Sub(u, v));
    }
}
#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"

namespace Math {
    template<typename T>
	INLINE vec<T, 3> vec3Create(T x, T y, T z) {
		return vec<T, 3>(x, y, z);
	}

    template<typename T>
    INLINE vec<T, 3> vec3FromVec4(vec<T, 4> u) {
        return vec<T, 3>(u.x, u.y, u.z);
    }

    template<typename T>
	INLINE vec<T, 3> vec3Zero() { return vec<T, 3>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

    template<typename T>
	INLINE vec<T, 3> vec3Up() { return vec<T, 3>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

    template<typename T>
	INLINE vec<T, 3> vec3Down() { return vec<T, 3>(static_cast<T>(0), -static_cast<T>(1), static_cast<T>(0)); }

    template<typename T>
	INLINE vec<T, 3> vec3Left() { return vec<T, 3>(-static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

    template<typename T>
	INLINE vec<T, 3> vec3Right() { return vec<T, 3>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
	
    template<typename T> // Look into might have to be other way around but also could be dependant on LHR or RHR.
	INLINE vec<T, 3> vec3Forward() { return vec<T, 3>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

    template<typename T>
	INLINE vec<T, 3> vec3Backward() { return vec<T, 3>(static_cast<T>(0), static_cast<T>(0), -static_cast<T>(1)); }

    template<typename T>
    INLINE float vec3Dot(vec<T, 3> u, vec<T, 3> v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    template<typename T>
    INLINE vec<T, 3> vec3Cross(vec<T, 3> u, vec<T, 3> v) {
        return vec3(
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y - v.x
        );
    }

    template<typename T>
    INLINE T vec3SquaredLength(vec<T, 3> v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    template<typename T>
    INLINE T vec3Length(vec<T, 3> v) {
        return sqrt(vec3SquaredLength(v));
    }

    template<typename T>
    INLINE void vec3Normalize(vec<T, 3>* v) {
        using M = MathTraits<T>;

        const T len = vec3Length(*v);
        v->x = (len > M::EPSILON) ? v->x / len : static_cast<T>(0);
        v->y = (len > M::EPSILON) ? v->y / len : static_cast<T>(0);
        v->z = (len > M::EPSILON) ? v->z / len : static_cast<T>(0);
    }

    template<typename T>
    INLINE vec<T, 3> vec3Normalized(vec<T, 3> v) {
        vec3Normalize(&v);
        return v;
    }

    /**
    *   @brief Compares all elements of u and v and ensures the differense is less than the tolerance.
    *
    *   @param u The first vector.
    *   @param v The second vector.
    *   @param epsilon The difference tolerance.
    *   @return True if within epsilon; otherwise false.
    */
    template<typename T>
    INLINE char vec3Compare(vec<T, 3> u, vec<T, 3> v, T epsilon) {
        return (abs(u.x - v.x) <= epsilon) && (abs(u.y - v.y) <= epsilon) && (abs(u.z - v.z) <= epsilon);
    }

    template<typename T>
    INLINE T vec3Distance(vec<T, 3> u, vec<T, 3> v) {
        return vec3Length(u - v);
    }

    using vec3 = vec<float, 3>;
    using vec3d = vec<double, 3>;
}
#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"

namespace Math {
    template<typename T, int R, int C>
    struct Matrix;
}

template<typename T>
INLINE Math::vec<T, 3> vec3Create(T x, T y, T z) {
    return Math::vec<T, 3>(x, y, z);
}

template<typename T>
INLINE Math::vec<T, 3> vec3FromVec4(Math::vec<T, 4> u) {
    return Math::vec<T, 3>(u.x, u.y, u.z);
}

template<typename T>
INLINE Math::vec<T, 3> vec3Zero() { return Math::vec<T, 3>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 3> vec3One() { return Math::vec<T, 3>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)); }

template<typename T>
INLINE Math::vec<T, 3> vec3Up() { return Math::vec<T, 3>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 3> vec3Down() { return Math::vec<T, 3>(static_cast<T>(0), -static_cast<T>(1), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 3> vec3Left() { return Math::vec<T, 3>(-static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 3> vec3Right() { return Math::vec<T, 3>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

template<typename T> // Look into might have to be other way around but also could be dependant on LHR or RHR.
INLINE Math::vec<T, 3> vec3Forward() { return Math::vec<T, 3>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

template<typename T>
INLINE Math::vec<T, 3> vec3Backward() { return vec<T, 3>(static_cast<T>(0), static_cast<T>(0), -static_cast<T>(1)); }

template<typename T>
INLINE float vec3Dot(Math::vec<T, 3> u, Math::vec<T, 3> v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template<typename T>
INLINE Math::vec<T, 3> vec3Cross(Math::vec<T, 3> u, Math::vec<T, 3> v) {
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

template<typename T>
INLINE T vec3SquaredLength(Math::vec<T, 3> v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<typename T>
INLINE T vec3Length(Math::vec<T, 3> v) {
    return sqrt(vec3SquaredLength(v));
}

template<typename T>
INLINE void vec3Normalize(Math::vec<T, 3>* v) {
    using M = MathTraits<T>;

    const T len = vec3Length(*v);
    v->x = (len > M::EPSILON) ? v->x / len : static_cast<T>(0);
    v->y = (len > M::EPSILON) ? v->y / len : static_cast<T>(0);
    v->z = (len > M::EPSILON) ? v->z / len : static_cast<T>(0);
}

template<typename T>
INLINE Math::vec<T, 3> vec3Normalized(Math::vec<T, 3> v) {
    Math::vec<T, 3> normalized = vec3Normalize(v);
    return normalized;
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
INLINE char vec3Compare(Math::vec<T, 3> u, Math::vec<T, 3> v, T epsilon) {
    return (abs(u.x - v.x) <= epsilon) && (abs(u.y - v.y) <= epsilon) && (abs(u.z - v.z) <= epsilon);
}

template<typename T>
INLINE T vec3Distance(Math::vec<T, 3> u, Math::vec<T, 3> v) {
    return vec3Length(u - v);
}

template<typename T>
INLINE Math::vec<T, 3> vec3MulMat3(Math::Matrix<T, 3, 3> m, Math::vec<T, 3> v) {
    return Math::vec<T, 3>(
        v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[7],
        v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[8],
        v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[9]
    );
}

template<typename T>
INLINE Math::vec<T, 3> vec3MulMat4(Math::Matrix<T, 4, 4> m, Math::vec<T, 3> v) {
    return Math::vec<T, 3>(
        v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[8] + m.data[12],
        v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[9] + m.data[13],
        v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[10] + m.data[14]
    );
}

using vec3 = Math::vec<float, 3>;
using vec3d = Math::vec<double, 3>;
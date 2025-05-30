#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Constants.h"
#include "Functions.hpp"

/**
   *   @brief Create and returns a new 2-element vector
   *
   *   @param x The 1st element's value
   *   @param y The 2nd element's value
   *   @return A new 2-element vector.
   */
template<typename T>
INLINE Math::vec<T, 2> vec2Create(T x, T y) {
    return Math::vec<T, 2>(x, y);
}

template<typename T>
INLINE Math::vec<T, 2> vec2Zero() { return Math::vec<T, 2>(static_cast<T>(0), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 2> vec2One() { return Math::vec<T, 2>(static_cast<T>(1), static_cast<T>(1)); }

template<typename T>
INLINE Math::vec<T, 2> vec2Up() { return Math::vec2(static_cast<T>(0), static_cast<T>(1)); }

template<typename T>
INLINE Math::vec<T, 2> vec2Down() { return Math::vec2(static_cast<T>(0), -static_cast<T>(1)); }

template<typename T>
INLINE Math::vec<T, 2> vec2Left() { return Math::vec2(-static_cast<T>(1), static_cast<T>(0)); }

template<typename T>
INLINE Math::vec<T, 2> vec2Right() { return Math::vec2(static_cast<T>(1), static_cast<T>(0)); }

template<typename T>
INLINE T vec2Dot(Math::vec<T, 2> u, Math::vec<T, 2> v) {
    return u.x * v.x + u.y * v.y;
}

template<typename T>
INLINE T vec2SquaredLength(Math::vec<T, 2> v) {
    return v.x * v.x + v.y * v.y;
}

template<typename T>
INLINE T vec2Length(Math::vec<T, 2> v) {
    return sqrt(vec2SquaredLength(v));
}

template<typename T>
INLINE void vec2Normalize(Math::vec<T, 2>* v) {
    using M = MathTraits<T>;

    const T len = vec2Length(*v);
    v->x = (len > M::EPSILON) ? v->x / len : static_cast<T>(0);
    v->y = (len > M::EPSILON) ? v->y / len : static_cast<T>(0);
}

template<typename T>
INLINE Math::vec<T, 2> vec2Normalized(Math::vec<T, 2> vector) {
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
template<typename T>
INLINE char vec2Compare(Math::vec<T, 2> u, Math::vec<T, 2> v, T epsilon) {
    return (abs(u.x - v.x) <= epsilon) && (abs(u.y - v.y) <= epsilon);
}

template<typename T>
INLINE T vec2Distance(Math::vec<T, 2> u, Math::vec<T, 2> v) {
    return vec2Length((u - v));
}

using vec2 = Math::vec<float, 2>;
using vec2d = Math::vec<double, 2>;
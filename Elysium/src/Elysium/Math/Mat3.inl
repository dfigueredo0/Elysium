#pragma once

#include "Vec.hpp"
#include "Matrix.hpp"

// Tait-Bryan Angles -- intersection of two non-homologous planes -- most common convention Z(a)X(b)Y(c)
   // Assuming a frame with unit vectors (the angle theta is negative):
   //      sin(theta) = -x3                                theta = arcsin(-x3)
   //      sin(psi) = x2/sqrt(1-(x3)^2)                    psi = arcsin(x2/sqrt(1-(x3)^2))
   //      sin(phi) = y3/sqrt(1-(x3)^2)                    phi = arcsin(y3/sqrt(1-(x3)^2))
template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3EulerX(T rad) {
    Math::Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();;
    T c = Math::cos(rad), s = Math::sin(rad);

    mat(1, 1) = c;
    mat(1, 2) = -s;
    mat(2, 1) = s;
    mat(2, 2) = c;

    return mat;
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3EulerY(T rad) {
    Math::Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    T c = Math::cos(rad), s = Math::sin(rad);

    mat(0, 0) = c;
    mat(0, 2) = s;
    mat(2, 0) = -s;
    mat(2, 2) = c;

    return mat;
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3EulerZ(T rad) {
    Math::Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    T c = Math::cos(rad), s = Math::sin(rad);

    mat(0, 0) = c;
    mat(0, 1) = -s;
    mat(1, 0) = s;
    mat(1, 1) = c;

    return mat;
}

//Def: ZYX order.
template<typename T>
INLINE Math::Matrix<T, 3, 3> mat33uler(T xRad, T yRad, T zRad) {
    return mat3EulerX(xRad) * mat3EulerY(yRad) * mat3EulerZ(zRad);
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3Translation2D(const Math::vec<T, 2>& pos) {
    Math::Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    mat.data[2] = pos.x;
    mat.data[5] = pos.y;
    return mat;
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3Translation3D(const Math::vec<T, 3>& pos) {
    Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    mat.data[2] = pos.x;
    mat.data[5] = pos.y;
    mat.data[8] = pos.z;
    return mat;
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3Scale2D(const Math::vec<T, 2>& scale) {
    Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    mat.data[0] = scale.x;
    mat.data[4] = scale.y;
    return mat;
}

template<typename T>
INLINE Math::Matrix<T, 3, 3> mat3Scale3D(const Math::vec<T, 3>& scale) {
    Matrix<T, 3, 3> mat = Math::identity<T, 3, 3>();
    mat.data[0] = scale.x;
    mat.data[4] = scale.y;
    mat.data[8] = scale.z;
    return mat;
}

/**
*   @brief Returns a forward vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Forward(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> forward{ mat.data[2], mat.data[5], mat.data[8] };
    vec3Normalize(&forward);
    return forward;
}

/**
*   @brief Returns a backward vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Backward(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> backward{ -mat.data[2], -mat.data[5], -mat.data[8] };
    vec3Normalize(&backward);
    return backward;
}

/**
*   @brief Returns a up vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Up(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> up{ mat.data[1], mat.data[4], mat.data[7] };
    vec3Normalize(&up);
    return up;
}

/**
*   @brief Returns a down vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Down(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> down{ -mat.data[1], -mat.data[4], -mat.data[7] };
    vec3Normalize(&down);
    return down;
}

/**
*   @brief Returns a left vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Left(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> left{ -mat.data[0], -mat.data[3], -mat.data[6] };
    vec3Normalize(&left);
    return left;
}

/**
*   @brief Returns a right vector relative to the provided matrix.
*/
template<typename T>
INLINE Math::vec<T, 3> mat3Right(const Math::Matrix<T, 3, 3>& mat) {
    Math::vec<T, 3> right{ mat.data[0], mat.data[3], mat.data[6] };
    vec3Normalize(&right);
    return right;
}

using mat3 = Math::Matrix<float, 3, 3>;
using mat3d = Math::Matrix<double, 3, 3>;
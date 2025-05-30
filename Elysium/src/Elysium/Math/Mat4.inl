#pragma once

#include "Vec.hpp"
#include "Matrix.hpp"

// Tait-Bryan Angles -- intersection of two non-homologous planes -- most common convention Z(a)X(b)Y(c)
  // Assuming a frame with unit vectors (the angle theta is negative):
  //      sin(theta) = -x3                                theta = arcsin(-x3)
  //      sin(psi) = x2/sqrt(1-(x3)^2)                    psi = arcsin(x2/sqrt(1-(x3)^2))
  //      sin(phi) = y3/sqrt(1-(x3)^2)                    phi = arcsin(y3/sqrt(1-(x3)^2))
template<typename T>
Math::Matrix<T, 4, 4> mat4EulerX(T rad) {
    Math::Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();
    T c = cos(rad), s = sin(rad);

    mat(1, 1) = c;
    mat(1, 2) = -s;
    mat(2, 1) = s;
    mat(2, 2) = c;

    return mat;
}

template<typename T>
Math::Matrix<T, 4, 4> mat4EulerY(T rad) {
    Math::Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();
    T c = cos(rad), s = sin(rad);

    mat(0, 0) = c;
    mat(0, 2) = s;
    mat(2, 0) = -s;
    mat(2, 2) = c;

    return mat;
}

template<typename T>
Math::Matrix<T, 4, 4> mat4EulerZ(T rad) {
    Math::Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();
    T c = cos(rad), s = sin(rad);

    mat(0, 0) = c;
    mat(0, 1) = -s;
    mat(1, 0) = s;
    mat(1, 1) = c;

    return mat;
}

template<typename T>
Math::Matrix<T, 4, 4> mat4Euler(T xRad, T yRad, T zRad) {
    return mat4EulerX<T>(xRad) * mat4EulerY<T>(yRad) * mat4EulerZ<T>(zRad);
}

template<typename T>
Math::Matrix<T, 4, 4> mat4Translation(const Math::vec<T, 3>& pos) {
    Math::Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();
    mat(0, 3) = pos.x;
    mat(1, 3) = pos.y;
    mat(2, 3) = pos.z;
    return mat;
}

template<typename T>
Math::Matrix<T, 4, 4> mat4Scale(const Math::vec<T, 3>& scale) {
    Math::Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();
    mat(0, 0) = scale.x;
    mat(1, 1) = scale.y;
    mat(2, 2) = scale.z;
    return mat;
}

template<typename T>
Math::vec<T, 3> mat4Forward(const Math::Matrix<T, 4, 4>& mat) {
    Math::vec<T, 3> forward{ mat.data[2], mat.data[6], mat.data[10] };
    vec3Normalize(&forward);
    return forward;
}

template<typename T>
Math::vec<T, 3> mat4Right(const Math::Matrix<T, 4, 4>& mat) {
    Math::vec<T, 3> right{ mat.data[0], mat.data[4], mat.data[8] };
    vec3Normalize(&right);
    return right;
}

template<typename T>
INLINE Math::vec<T, 3> Mat4MulVec3(Math::Matrix<T, 4, 4> m, Math::vec<T, 3> v) {
    return Math::vec<T, 3>(
        v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2] + m.data[3],
        v.x * m.data[4] + v.y * m.data[5] + v.z * m.data[6] + m.data[7],
        v.x * m.data[8] + v.y * m.data[9] + v.z * m.data[10] + m.data[11],
        );
}

template<typename T>
INLINE Math::vec<T, 4> Mat4MulVec4(Math::Matrix<T, 4, 4> m, Math::vec<T, 4> v) {
    return Math::vec<T, 4>(
        v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2] + v.w * m.data[3],
        v.x * m.data[4] + v.y * m.data[5] + v.z * m.data[6] + v.w * m.data[7],
        v.x * m.data[8] + v.y * m.data[9] + v.z * m.data[10] + v.w * m.data[11],
        v.x * m.data[12] + v.y * m.data[13] + v.z * m.data[14] + v.w * m.data[15]
    );
}

using mat4 = Math::Matrix<float, 4, 4>;
using mat4d = Math::Matrix<double, 4, 4>;
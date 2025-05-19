#pragma once

#include "Matrix.hpp"

namespace Math {
   // Tait-Bryan Angles -- intersection of two non-homologous planes -- most common convention Z(a)X(b)Y(c)
   // Assuming a frame with unit vectors (the angle theta is negative):
   //      sin(theta) = -x3                                theta = arcsin(-x3)
   //      sin(psi) = x2/sqrt(1-(x3)^2)                    psi = arcsin(x2/sqrt(1-(x3)^2))
   //      sin(phi) = y3/sqrt(1-(x3)^2)                    phi = arcsin(y3/sqrt(1-(x3)^2))
    template<typename T>
    Matrix<T, 4, 4> mat4EulerX(T rad) {
        Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
        T c = cos(rad), s = sin(rad);

        mat(1, 1) = c;
        mat(1, 2) = -s;
        mat(2, 1) = s;
        mat(2, 2) = c;

        return mat;
    }

    template<typename T>
    Matrix<T, 4, 4> mat4EulerY(T rad) {
        Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
        T c = cos(rad), s = sin(rad);

        mat(0, 0) = c;
        mat(0, 2) = s;
        mat(2, 0) = -s;
        mat(2, 2) = c;

        return mat;
    }

    template<typename T>
    Matrix<T, 4, 4> mat4EulerZ(T rad) {
        Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
        T c = cos(rad), s = sin(rad);

        mat(0, 0) = c;
        mat(0, 1) = -s;
        mat(1, 0) = s;
        mat(1, 1) = c;

        return mat;
    }

    template<typename T>
    Matrix<T, 4, 4> mat4Euler(T xRad, T yRad, T zRad) {
        return mat4EulerX<T>(xRad) * mat4EulerY<T>(yRad) * mat4EulerZ<T>(zRad);
    }

    template<typename T>
    Matrix<T, 4, 4> mat4Translation(const vec<T, 3>& pos) {
        Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
        mat(0, 3) = pos.x;
        mat(1, 3) = pos.y;
        mat(2, 3) = pos.z;
        return mat;
    }

    template<typename T>
    Matrix<T, 4, 4> mat4Scale(const vec<T, 3>& scale) {
        Matrix<T, 4, 4> mat = Matrix<T, 4, 4>::identity();
        mat(0, 0) = scale.x;
        mat(1, 1) = scale.y;
        mat(2, 2) = scale.z;
        return mat;
    }

    template<typename T>
    vec<T, 3> mat4Forward(const Matrix<T, 4, 4>& mat) {
        vec<T, 3> forward{ mat.data[2], mat.data[6], mat.data[10] };
        vec3Normalize(&forward);
        return forward;
    }

    template<typename T>
    vec<T, 3> mat4Right(const Matrix<T, 4, 4>& mat) {
        vec<T, 3> right{ mat.data[0], mat.data[4], mat.data[8] };
        vec3Normalize(&right);
        return right;
    }

    using mat4 = Matrix<float, 4, 4>;
    using mat4d = Matrix<double, 4, 4>;
}
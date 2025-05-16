#pragma once

#include "Elysium/Core.h"
#include "Vec4.hpp"
#include <string.h>
#include <cstddef>

namespace Math {
    template<typename T, int R, int C>
    struct Matrix {
        alignas(16) T data[R * C];

        INLINE Matrix() {
            memset(data, 0, sizeof(data));
        }

        INLINE T& operator()(int row, int col) {
            assert(row < R && col < C);
            return data[row * C + col];
        }

        INLINE const T& operator()(int row, int col) const {
            assert(row < R && col < C);
            return data[row * C + col];
        }

        static Matrix<T, R, C> identity() {
            ELY_ASSERT(R == C, "Identity only defined for square matrices.");
            Matrix<T, R, C> mat;
            for (int i = 0; i < Rows; ++i)
                mat(i, i) = static_cast<T>(1);
            return mat;
        }

        // Multiplication with another matrix (only valid when dimensions match)
        template<int U>
        Matrix<T, R, U> operator*(const Matrix<T, C, U>& rhs) const {
            Matrix<T, R, U> result;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < U; ++j) {
                    for (int k = 0; k < C; ++k) {
                        result(i, j) += (*this)(i, k) * rhs(k, j);
                    }
                }
            }
            return result;
        }

        Matrix<T, R, C> orthonormalize() const {
            ELY_ASSERT(R == C, "Only square matrices can be orthonormalized.");
            ELY_ASSERT(C <= 4, "Only up to 4x4 orthonormalization is supported.");

            Matrix<T, R, C> result;

            // Extract columns as vecN
            vec4 col[4]; // worst case
            for (int i = 0; i < C; ++i)
                for (int j = 0; j < R; ++j)
                    col[i].elements[j] = (*this)(j, i); // column-major access

            // Gram-Schmidt Process
            for (int i = 0; i < C; ++i) {
                for (int j = 0; j < i; ++j) {
                    float dot = vec4Dot(col[i], col[j]);
                    for (int k = 0; k < R; ++k)
                        col[i].elements[k] -= dot * col[j].elements[k];
                }
                col[i] = vec4Normalized(col[i]);
            }

            // Repack result
            for (int i = 0; i < C; ++i)
                for (int j = 0; j < R; ++j)
                    result(j, i) = col[i].elements[j];

            return result;

        }

        Matrix<T, R, C> getCof() {

        }

        Matrix <T, R, C> getDet() {

        }

        Matrix<T, R, C> inverse() const {
            ELY_ASSERT(R == C, "Only square matrices can be inversed.");


        }


        INLINE vec4 getRow(int i) const {
            vec4 result;
            for (int j = 0; j < 4; ++j)
                result.elements[j] = data[i * 4 + j];
            return result;
        }

        INLINE void setRow(int i, const vec4& row) {
            for (int j = 0; j < 4; ++j)
                data[i * 4 + j] = row.elements[j];
        }
    };

    using mat2 = Matrix<float, 2, 2>;
    using mat2x3 = Matrix<float, 2, 3>;
    using mat2x4 = Matrix<float, 2, 4>;

    using mat3 = Matrix<float, 3, 3>;
    using mat3x2 = Matrix<float, 3, 2>;
    using mat3x4 = Matrix<float, 3, 4>;

    using mat4 = Matrix<float, 4, 4>;
    using mat4x2 = Matrix<float, 4, 2>;
    using mat4x3 = Matrix<float, 4, 3>;
}
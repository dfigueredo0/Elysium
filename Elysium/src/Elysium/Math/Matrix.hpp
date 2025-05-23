#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"
#include <string.h>

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

        static constexpr Matrix<T, R, C> identity() {
            ELY_ASSERT(R == C, "Identity only defined for square matrices.");
            Matrix<T, R, C> mat;
            for (int i = 0; i < R; ++i)
                mat(i, i) = static_cast<T>(1);
            return mat;
        }

        Matrix<T, R, C> operator+(const Matrix<T, R, C>& rhs) const {
            Matrix<T, R, C> result;
            for (int i = 0; i < R * C; ++i)
                result.data[i] = this->data[i] + rhs.data[i];
            return result;
        }

        Matrix<T, R, C> operator-(const Matrix<T, R, C>& rhs) const {
            Matrix<T, R, C> result;
            for (int i = 0; i < R * C; ++i)
                result.data[i] = this->data[i] - rhs.data[i];
            return result;
        }

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

        Matrix<T, R, C> operator/(const Matrix<T, R, C>& rhs) const {
            Matrix<T, R, C> result;
            for (int i = 0; i < R * C; ++i)
                result.data[i] = this->data[i] / rhs.data[i];
            return result;
        }

        Matrix<T, R, C>& operator+=(const Matrix<T, R, C>& rhs) {
            for (int i = 0; i < R * C; ++i)
                this->data[i] += rhs.data[i];
            return *this;
        }

        
        Matrix<T, R, C>& operator-=(const Matrix<T, R, C>& rhs) {
            for (int i = 0; i < R * C; ++i)
                this->data[i] -= rhs.data[i];
            return *this;
        }

        
        Matrix<T, R, C>& operator*=(const Matrix<T, R, C>& rhs) {
            *this = (*this) * rhs;
            return *this;
        }

        Matrix<T, R, C>& operator/=(const Matrix<T, R, C>& rhs) {
            for (int i = 0; i < R * C; ++i)
                this->data[i] /= rhs.data[i];
            return *this;
        }

        bool operator==(const Matrix<T, R, C>& rhs) const {
            for (int i = 0; i < R * C; ++i)
                if (this->data[i] != rhs.data[i])
                    return false;
            return true;
        }

        bool operator!=(const Matrix<T, R, C>& rhs) const {
            return !(*this == rhs);
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

        static Matrix<T, R - 1, C - 1> getCofactor(const Matrix<T, R, C>& mat, int skipRow, int skipCol) {
            Matrix<T, R - 1, C - 1> result;
            int r = 0;

            for (int i = 0; i < R; ++i) {
                if (i == skipRow) continue;
                int c = 0;
                for (int j = 0; j < C; ++j) {
                    if (j == skipCol) continue;
                    result(r, c++) = mat(i, j);
                }
                ++r;
            }

            return result;
        }

        template<int N>
        static T getDeterminant(const Matrix<T, N, N>& mat) {
            if constexpr (N == 1) {
                return mat(0, 0);
            }

            if constexpr (N == 2) {
                return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
            }

            T result = 0;
            int sign = 1;

            for (int col = 0; col < N; ++col) {
                auto cof = getCofactor(mat, 0, col);
                result += sign * mat(0, col) * getDeterminant(cof);
                sign *= -1;
            }

            return result;
        }

        template<int N>
        static Matrix<T, N, N> getAdjoint(const Matrix<T, N, N>& mat) {
            Matrix<T, N, N> adj;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    auto cof = getCofactor(mat, i, j);
                    float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                    adj(j, i) = sign * getDeterminant(cof);
                }
            }

            return adj;
        }

        template<int N>
        static Matrix<T, N, N> getInverse(const Matrix<T, N, N>& mat) {
            T det = getDeterminant(mat);
            ELY_ASSERT(fabs(det) > EPSILON, "Matrix is singular or nearly singular.");

            Matrix<T, N, N> adj = getAdjoint(mat);
            Matrix<T, N, N> inv;

            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    inv(i, j) = adj(i, j) / det;

            return inv;
        }

        static Matrix<T, C, R> getTransposition(const Matrix<T, R, C>& mat) {
            Matrix<T, C, R> result;

            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    result(j, i) = mat(i, j);
                }
            }

            return result;
        }

        Matrix<T, C, R> transpose() const {
            return getTransposition(*this);
        }

        INLINE vec<T, C> getRow(int i) const {
            vec<T, C> result;
            for (int j = 0; j < C; ++j)
                result.elements[j] = data[i * C + j];
            return result;
        }

        INLINE void setRow(int i, const vec<T, C>& row) {
            for (int j = 0; j < C; ++j)
                data[i * C + j] = row.elements[j];
        }
    };

    using mat2f = Matrix<float, 2, 2>;
    using mat2x3f = Matrix<float, 2, 3>;
    using mat2x4f = Matrix<float, 2, 4>;

    using mat2d = Matrix<double, 2, 2>;
    using mat2x3d = Matrix<double, 2, 3>;
    using mat2x4d = Matrix<double, 2, 4>;

#include "Mat3.inl"
    using mat3x2f = Matrix<float, 3, 2>;
    using mat3x4f = Matrix<float, 3, 4>;
    using mat3x2d = Matrix<double, 3, 2>;
    using mat3x4d = Matrix<double, 3, 4>;

#include "Mat4.inl"
    using mat4x2f = Matrix<float, 4, 2>;
    using mat4x3f = Matrix<float, 4, 3>;
    using mat4x2d = Matrix<double, 4, 2>;
    using mat4x3d = Matrix<double, 4, 3>;
}
#pragma once

#include "Elysium/Core.h"
#include "Vec4.hpp"
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

        template<typename T, int R, int C>
        Matrix<T, R - 1, C - 1> getCofactor(const Matrix<T, R, C>& mat, int skipRow, int skipCol) {
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

        template<typename T, int N>
        T getDeterminant(const Matrix<T, N, N>& mat) {
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

        template<typename T, int N>
        Matrix<T, N, N> getAdjoint(const Matrix<T, N, N>& mat) {
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

        template<typename T, int N>
        Matrix<T, N, N> getInverse(const Matrix<T, N, N>& mat) {
            T det = getDeterminant(mat);
            ELY_ASSERT(fabs(det) > EPSILON, "Matrix is singular or nearly singular.");

            Matrix<T, N, N> adj = getAdjoint(mat);
            Matrix<T, N, N> inv;

            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    inv(i, j) = adj(i, j) / det;

            return inv;
        }

        template<typename T, int R, int C>
        Matrix<T, C, R> getTransposition(const Matrix<T, R, C>& mat) {
            Matrix<T, C, R> result;

            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    result(j, i) = mat(i, j);
                }
            }

            return result;
        }

#pragma region TODO
        // TODO: make generic
        INLINE mat4 mat4Translation(vec3 pos) {
            mat4 mat = mat4::identity();
            mat.data[12] = pos.x;
            mat.data[13] = pos.y;
            mat.data[14] = pos.z;
            return mat;
        }

        INLINE mat4 mat4Scale(vec3 scale) {
            mat4 mat = mat4::identity();
            mat.data[0] = scale.x;
            mat.data[5] = scale.y;
            mat.data[10] = scale.z;
            return mat;
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
#pragma endregion

#pragma region MoveToMat4.inl
        // Tait-Bryan Angles -- intersection of two non-homologous planes -- most common convention Z(a)X(b)Y(c)
        // Assuming a frame with unit vectors (the angle theta is negative):
        //      sin(theta) = -x3                                theta = arcsin(-x3)
        //      sin(psi) = x2/sqrt(1-(x3)^2)                    psi = arcsin(x2/sqrt(1-(x3)^2))
        //      sin(phi) = y3/sqrt(1-(x3)^2)                    phi = arcsin(y3/sqrt(1-(x3)^2))

        INLINE constexpr mat4 mat4EulerX(float rad) {
            mat4 mat = mat4::identity();
            float c = cos(rad), s = sin(rad);

            mat(1, 1) = c;
            mat(1, 2) = -s;
            mat(2, 1) = s;
            mat(2, 2) = c;

            return mat;
        }
        
        INLINE constexpr mat4 mat4EulerY(float rad) {
            mat4 mat = mat4::identity();
            float c = cos(rad), s = sin(rad);

            mat(0, 0) = c;
            mat(0, 2) = s;
            mat(2, 0) = -s;
            mat(2, 2) = c;

            return mat;
        }
        
        INLINE constexpr mat4 mat4EulerZ(float rad) {
            mat4 mat = mat4::identity();
            float c = cos(rad), s = sin(rad);

            mat(0, 0) = c;
            mat(0, 1) = -s;
            mat(1, 0) = s;
            mat(1, 1) = c;

            return mat;
        }

        //Def: ZYX order.
        INLINE constexpr mat4 mat4Euler(float xRad, float yRad, float zRad) {
            return mat4EulerX(xRad) * mat4EulerY(yRad) * mat4EulerZ(zRad);
        }

        /**
        *   @brief Returns a forward vector relative to the provided matrix.
        */
        INLINE vec3 mat4Forward(mat4 mat) {
            vec3 forward;
            forward.x = mat.data[2];
            forward.y = mat.data[6];
            forward.z = mat.data[10];
            vec3Normalize(&forward);
            return forward;
        }

        /**
        *   @brief Returns a backward vector relative to the provided matrix.
        */
        INLINE vec3 mat4Backward(mat4 mat) {
            vec3 backward;
            backward.x = -mat.data[2];
            backward.y = -mat.data[6];
            backward.z = -mat.data[10];
            vec3Normalize(&backward);
            return backward;
        }

        /**
        *   @brief Returns a up vector relative to the provided matrix.
        */
        INLINE vec3 mat4Up(mat4 mat) {
            vec3 up;
            up.x = mat.data[1];
            up.y = mat.data[5];
            up.z = mat.data[9];
            vec3Normalize(&up);
            return up;
        }

        /**
        *   @brief Returns a down vector relative to the provided matrix.
        */
        INLINE vec3 mat4Down(mat4 mat) {
            vec3 down;
            down.x = -mat.data[1];
            down.y = -mat.data[5];
            down.z = -mat.data[9];
            vec3Normalize(&down);
            return down;
        }
       
        /**
        *   @brief Returns a left vector relative to the provided matrix.
        */
        INLINE vec3 mat4Left(mat4 mat) {
            vec3 left;
            left.x = -mat.data[0];
            left.y = -mat.data[4];
            left.z = -mat.data[8];
            vec3Normalize(&left);
            return left;
        }

        /**
        *   @brief Returns a right vector relative to the provided matrix.
        */
        INLINE vec3 mat4Right(mat4 mat) {
            vec3 right;
            right.x = mat.data[0];
            right.y = mat.data[4];
            right.z = mat.data[8];
            vec3Normalize(&right);
            return right;
        }
#pragma endregion
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
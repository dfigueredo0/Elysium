#pragma once

#include "Elysium/Core.h"
#include "SIMD/Platform.h"
#include "Vec.hpp"
#include <cstring>
#include <cassert>
#include <type_traits>
#include <string.h>

namespace Math {
    template<typename T>
    struct SimdAlignment {
        static constexpr size_t value = alignof(T);
    };

#if SIMD_LEVEL_AVX512 || SIMD_LEVEL_AVX2
    template<>
    struct SimdAlignment<double> {
        static constexpr size_t value = 32;
    };
#endif

#if SIMD_LEVEL_SSE41
    template<>
    struct SimdAlignment<float> {
        static constexpr size_t value = 16;
    };
#endif

    template<typename T, int R, int C>
    struct alignas(SimdAlignment<T>::value) Matrix {
        alignas(SimdAlignment<T>::value) T data[R * C];

        INLINE Matrix() {
            if constexpr (std::is_same_v<T, double> && (SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX512)) {
                constexpr int N = (R * C + 3) / 4;
                for (int i = 0; i < N; ++i)
                    _mm256_store_pd(&data[i * 4], _mm256_setzero_pd());
            }
            else if constexpr (std::is_same_v<T, float> && SIMD_LEVEL_SSE41) {
                constexpr int N = (R * C + 3) / 4;
                for (int i = 0; i < N; ++i)
                    _mm_store_ps(&data[i * 4], _mm_setzero_ps());
            }
            else {
                std::memset(data, 0, sizeof(data));
            }
            static_assert(alignof(Matrix<T, R, C>) >= SimdAlignment<T>::value, "Matrix not properly aligned for SIMD.");
        }

        constexpr INLINE Matrix(std::initializer_list<T> list) {
            int i = 0;
            for (auto it = list.begin(); it != list.end() && i < R * C; ++it, ++i)
                data[i] = *it;

            while (i < R * C)
                data[i++] = T(0);
        }

        constexpr INLINE Matrix(T scalar) {
            for (int i = 0; i < R * C; ++i)
                data[i] = T(0);

            if constexpr (R == C) {
                for (int i = 0; i < R; ++i)
                    data[i * C + i] = scalar;
            }
        }

        INLINE T& operator()(int row, int col) {
            assert(row < R && col < C);
            return data[row * C + col];
        }

        INLINE const T& operator()(int row, int col) const {
            assert(row < R && col < C);
            return data[row * C + col];
        }

        INLINE Matrix<T, C, R> transpose() const {
            Matrix<T, C, R> result;
            for (int i = 0; i < R; ++i)
                for (int j = 0; j < C; ++j)
                    result(j, i) = (*this)(i, j);
            return result;
        }
    };


    template<typename T, int R, int C>
    static constexpr Matrix<T, R, C> identity() {
        ELY_ASSERT(R == C, "Identity only defined for square matrices.");
        Matrix<T, R, C> mat;
        for (int i = 0; i < R; ++i)
            mat(i, i) = static_cast<T>(1);
        return mat;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C> operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        Matrix<T, R, C> result;
        for (int i = 0; i < R * C; ++i)
            result.data[i] = lhs.data[i] + rhs.data[i];
        return result;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        Matrix<T, R, C> result;
        for (int i = 0; i < R * C; ++i)
            result.data[i] = lhs.data[i] - rhs.data[i];
        return result;
    }

    template<typename T, int R, int C, int U>
    INLINE Matrix<T, R, U> operator*(const Matrix<T, R, C>& lhs, const Matrix<T, C, U>& rhs) {
        Matrix<T, R, U> result;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < U; ++j) {
                result(i, j) = T(0);
                for (int k = 0; k < C; ++k)
                    result(i, j) += lhs(i, k) * rhs(k, j);
            }
        return result;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C> operator/(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        Matrix<T, R, C> result;
        for (int i = 0; i < R * C; ++i)
            result.data[i] = lhs.data[i] / rhs.data[i];
        return result;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C>& operator+=(Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        for (int i = 0; i < R * C; ++i)
            lhs.data[i] += rhs.data[i];
        return lhs;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C>& operator-=(Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        for (int i = 0; i < R * C; ++i)
            lhs.data[i] -= rhs.data[i];
        return lhs;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C>& operator*=(Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        lhs = lhs * rhs;
        return lhs;
    }

    template<typename T, int R, int C>
    INLINE Matrix<T, R, C>& operator/=(Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        for (int i = 0; i < R * C; ++i)
            lhs.data[i] /= rhs.data[i];
        return lhs;
    }

    template<typename T, int R, int C>
    INLINE bool operator==(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        for (int i = 0; i < R * C; ++i)
            if (lhs.data[i] != rhs.data[i]) return false;
        return true;
    }

    template<typename T, int R, int C>
    INLINE bool operator!=(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) {
        return !(lhs == rhs);
    }

    template<typename T, int R, int C>
    Matrix<T, R, C> orthonormalize(const Matrix<T, R, C>& mat) {
        ELY_ASSERT(R == C, "Only square matrices can be orthonormalized.");
        ELY_ASSERT(C <= 4, "Only up to 4x4 orthonormalization is supported.");

        Matrix<T, R, C> result;
        vec<T, R> basis[C];

        // Extract columns as vecN
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                basis[i][j] = mat(j, i);

        // Gram-Schmidt Orthonormalization
        for (int i = 0; i < C; ++i) {
            for (int j = 0; j < i; ++j) {
                T dot = vecDot(basis[i], basis[j]);
                for (int k = 0; k < R; ++k)
                    basis[i][k] -= dot * basis[j][k];
            }
            basis[i] = vecNormalized(basis[i]);
        }

        // Store back into result matrix
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                result(j, i) = basis[i][j];

        return result;
    }

    template<typename T, int R, int C>
    static Matrix<T, R - 1, C - 1> getCofactor(const Matrix<T, R, C>& mat, int skipRow, int skipCol) {
        static_assert(R > 1 && C > 1, "Cofactor not defined for 1x1 or smaller matrices.");

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

    template<typename T>
    static T getDeterminant(const Matrix<T, 1, 1>& mat) {
        return mat(0, 0);
    }

    template<typename T, int N>
    static T getDeterminant(const Matrix<T, N, N>& mat) {
        static_assert(N > 0, "Determinant not defined for 0x0 matrix.");

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

    template<typename T>
    static Matrix<T, 1, 1> getAdjoint(const Matrix<T, 1, 1>& mat) {
        Matrix<T, 1, 1> adj;
        adj(0, 0) = 1;
        return adj;
    }

    template<typename T, int N>
    static Matrix<T, N, N> getAdjoint(const Matrix<T, N, N>& mat) {
        static_assert(N > 1, "Adjoint not defined for 1x1 or smaller matrices.");
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

    template<typename T>
    static Matrix<T, 1, 1> getInverse(const Matrix<T, 1, 1>& mat) {
        T det = mat(0, 0);
        ELY_ASSERT(fabs(det) > Math::MathTraits<T>::EPSILON, "Matrix is singular.");
        Matrix<T, 1, 1> inv;
        inv(0, 0) = static_cast<T>(1) / det;
        return inv;
    }

    template<typename T, int N>
    static Matrix<T, N, N> getInverse(const Matrix<T, N, N>& mat) {
        T det = getDeterminant(mat);
        ELY_ASSERT(fabs(det) > Math::MathTraits<T>::EPSILON, "Matrix is singular or nearly singular.");

        Matrix<T, N, N> adj = getAdjoint(mat);
        Matrix<T, N, N> inv;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                inv(i, j) = adj(i, j) / det;

        return inv;
    }

    template<typename T, int C, int R>
    static Matrix<T, C, R> getTransposition(const Matrix<T, R, C>& mat) {
        Matrix<T, C, R> result;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                result(j, i) = mat(i, j);
            }
        }

        return result;
    }

    template<typename T>
    static Matrix<T, 4, 4> translateMatrix(const vec<T, 3>& position) {
        Matrix<T, 4, 4> result = Math::identity<T, 4, 4>();
        result(0, 3) = position.x;
        result(1, 3) = position.y;
        result(2, 3) = position.z;
        return result;
    }

    template<typename T>
    static Matrix<T, 4, 4> rotateMatrix(T rotation, vec<T, 3> axis) {
        Matrix<T, 4, 4> result = Math::identity<T, 4, 4>();

        T c = Math::cos(rotation);
        T s = Math::sin(rotation);

        // Assuming rotation about z-axis (0, 0, 1) for 2D camera
        result(0, 0) = c;
        result(0, 1) = -s;
        result(1, 0) = s;
        result(1, 1) = c;

        return result;
    }

    template<typename T>
    static Matrix<T, 4, 4> scaleMatrix(T scale) {
        Matrix<T, 4, 4> result = Math::identity<T, 4, 4>();

        result(0, 0) = scale;
        result(1, 1) = scale;
        result(2, 2) = scale;

        return result;
    }

    template<typename T, int R, int C>
    std::ostream& operator<<(std::ostream& os, const Math::Matrix<T, R, C>& mat) {
        for (int i = 0; i < R; ++i) {
            os << "[ ";
            for (int j = 0; j < C; ++j) {
                os << mat(i, j);
                if (j < C - 1) os << ", ";
            }
            os << " ]\n";
        }
        return os;
    }

    using mat2f = Matrix<float, 2, 2>;
    using mat2x3f = Matrix<float, 2, 3>;
    using mat2x4f = Matrix<float, 2, 4>;

    using mat2d = Matrix<double, 2, 2>;
    using mat2x3d = Matrix<double, 2, 3>;
    using mat2x4d = Matrix<double, 2, 4>;


    using mat3x2f = Matrix<float, 3, 2>;
    using mat3x4f = Matrix<float, 3, 4>;
    using mat3x2d = Matrix<double, 3, 2>;
    using mat3x4d = Matrix<double, 3, 4>;

    using mat4x2f = Matrix<float, 4, 2>;
    using mat4x3f = Matrix<float, 4, 3>;
    using mat4x2d = Matrix<double, 4, 2>;
    using mat4x3d = Matrix<double, 4, 3>;
}

#include "Mat3.inl"
#include "Mat4.inl"

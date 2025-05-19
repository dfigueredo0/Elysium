#pragma once

#include "Elysium/Core.h"
#include "SIMD/Common.h"
#include "Functions.hpp"

#include <iostream>
#include <initializer_list>

namespace Math {
	template<typename T, int N>
	struct alignas(16) vec {
		union {
			T elements[4];
			struct {
				T x, y, z, w;
			};
		};

		constexpr INLINE vec() {
			for (int i = 0; i < 4; ++i) {
				elements[i] = static_cast<T>(0);
			}
		}

		constexpr INLINE vec(std::initializer_list<T> list) {
			int i = 0;
			for (T v : list) {
				if (i < N)
					elements[i++] = v;
			}

			for (; i < 4; ++i) {
				elements[i] = static_cast<T>(0);
			}
		}

		constexpr vec(T x, T y, T z = T(0), T w = T(0)) : x(x), y(y), z(z), w(w) { }

		constexpr T& operator[](int index) { 
			return elements[index]; 
		}
		
		constexpr const T& operator[](int index) const { 
			return elements[index]; 
		}

		// vec2 from vec3
		template<typename U>
		constexpr vec(const vec<U, 3>& v) requires (N == 2) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

		// vec2 from vec4
		template<typename U>
		constexpr vec(const vec<U, 4>& v) requires (N == 2) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

		// vec3 from vec2
		template<typename U>
		constexpr vec(const vec<U, 2>& v, T z = T(0)) requires (N == 3) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(z) {}

		// vec4 from vec2
		template<typename U>
		constexpr vec(const vec<U, 2>& v, T z = T(0), T w = T(0)) requires (N == 4) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(z), w(w) {}

		//vec4 from vec3
		template<typename U>
		constexpr vec(const vec<U, 3>& v, T w = T(0)) requires (N == 4) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(w) {}
	};

#if SIMD_LEVEL_AVX512 || SIMD_LEVEL_AVX2 || SIMD_LEVEL_AVX
	struct alignas(32) vec<double, 4> {
		union {
			__m256d data;
			double elements[4];
			struct { double x, y, z, w; };
		};

		INLINE vec() : data(_mm256_setzero_pd()) {}
		INLINE vec(double x, double y, double z, double w) : data(_mm256_set_pd(w, z, y, x)) {}
	};

	struct alignas(32) vec<double, 3> {
		union {
			__m256d data;
			double elements[4];
			struct {
				union { double x, r, s, u; };
				union { double y, g, t, v; };
				union { double z, b, p, w; };
				double _padding[1];
			};
		};

		INLINE vec() : data(_mm256_setzero_pd()) {}
		INLINE vec(double x, double y, double z) : data(_mm256_set_pd(0.0, z, y, x)) {}
	};

	struct alignas(32) vec<double, 2> {
		union {
			__m256d data;
			double elements[4];
			struct {
				union { double x, r, s, u; };
				union { double y, g, t, v; };
				double _padding[2];
			};
		};

		INLINE vec() : data(_mm256_setzero_pd()) {}
		INLINE vec(double x, double y) : data(_mm256_set_pd(0.0, 0.0, y, x)) {}
	};
#endif

#if SIMD_LEVEL_SSE41
	struct alignas(16) vec<float, 4> {
		union {
			__m128 data;
			float elements[4];
			struct { float x, y, z, w; };
		};

		INLINE vec() : data(_mm_setzero_ps()) {}
		INLINE vec(float x, float y, float z, float w) : data(_mm_set_ps(w, z, y, x)) {}
	};

	struct alignas(16) vec<float, 3> {
		union {
			__m128 data;
			float elements[4];
			struct {
				union { float x, r, s, u; };
				union { float y, g, t, v; };
				union { float z, b, p, w; };
				float _padding;
			};
		};

		INLINE vec() : data(_mm_setzero_ps()) {}
		INLINE vec(float x, float y, float z) : data(_mm_set_ps(0.0f, z, y, x)) {}
	};

	struct alignas(16) vec<float, 2> {
		union {
			__m128 data;
			float elements[4];
			struct {
				union { float x, r, s, u; };
				union { float y, g, t, v; };
				float _padding[2];
			};
		};

		INLINE vec() : data(_mm_setzero_ps()) {}
		INLINE vec(float x, float y) : data(_mm_set_ps(0.0f, 0.0f, y, x)) {}
	};
#endif

	template<typename T, int N>
	INLINE vec<T, N> operator+(vec<T, N> const& u, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = u.elements[i] + v.elements[i];
		}
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator+(vec<T, N> const& v, const T& scalar) {
		vec<T, N> result = v;
		result += scalar;
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator+(const T& scalar, vec<T, N> const& v) {
		return v + scalar;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator-(vec<T, N> const& u, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = u.elements[i] - v.elements[i];
		}
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator-(vec<T, N> const& v, const T& scalar) {
		vec<T, N> result = v;
		result -= scalar;
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator-(const T& scalar, vec<T, N> const& v) {
		return v - scalar;
	}


	template<typename T, int N>
	INLINE vec<T, N> operator*(vec<T, N> const& u, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = u.elements[i] * v.elements[i];
		}
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator*(vec<T, N> const& v, const T& scalar) {
		vec<T, N> result = v;
		result *= scalar;
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator*(const T& scalar, vec<T, N> const& v) {
		return v * scalar;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator/(vec<T, N> const& u, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = v.elements[i] != static_cast<T>(0) ? u.elements[i] / v.elements[i] : static_cast<T>(0);
		}
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator/(vec<T, N> const& v, const T& scalar) {
		vec<T, N> result = v;
		result /= scalar;
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator/(const T& scalar, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result = v.elements[i] != static_cast<T>(0) ? scalar / v.elements[i] : static_cast<T>(0);
		}
		return result;
	}


	template<typename T, int N>
	INLINE vec<T, N>& operator+=(vec<T, N>& u, vec<T, N> const& v) {
		for (int i = 0; i < N; ++i) {
			u.elements[i] += v.elements[i];
		}
		return u;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator+=(vec<T, N>& v, const T& scalar) {
		for (int i = 0; i < N; ++i) {
			v.elements[i] += scalar;
		}
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator-=(vec<T, N>& u, vec<T, N> const& v) {
		for (int i = 0; i < N; ++i) {
			u.elements[i] -= v.elements[i];
		}
		return u;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator-=(vec<T, N>& v, const T& scalar) {
		for (int i = 0; i < N; ++i) {
			v.elements[i] -= scalar;
		}
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator*=(vec<T, N>& u, vec<T, N> const& v) {
		for (int i = 0; i < N; ++i) {
			u.elements[i] *= v.elements[i];
		}
		return u;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator*=(vec<T, N>& v, const T& scalar) {
		for (int i = 0; i < N; ++i) {
			v.elements[i] *= scalar;
		}
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator/=(vec<T, N>& u, vec<T, N> const& v) {
		for (int i = 0; i < N; ++i) {
			u.elements[i] /= v.elements[i];
		}
		return u;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator/=(vec<T, N>& v, const T& scalar) {
		for (int i = 0; i < N; ++i) {
			v.elements[i] = (scalar != static_cast<T>(0)) ? v.elements[i] / scalar : static_cast<T>(0);
		}
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator++(vec<T, N>& v) {
		for (int i = 0; i < N; ++i)
			++v.elements[i];
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator++(vec<T, N>& v, int) {
		vec<T, N> temp = v;
		for (int i = 0; i < N; ++i)
			++v.elements[i];
		return temp;
	}

	template<typename T, int N>
	INLINE vec<T, N>& operator--(vec<T, N>& v) {
		for (int i = 0; i < N; ++i)
			--v.elements[i];
		return v;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator--(vec<T, N>& v, int) {
		vec<T, N> temp = v;
		for (int i = 0; i < N; ++i)
			--v.elements[i];
		return temp;
	}

	template<typename T, typename U, int N>
	INLINE vec<T, N> operator%(vec<T, N> const& u, U scalar) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = mod(u.elements[i], scalar);
		}
		return result;
	}

	template<typename T, int N>
	INLINE vec<T, N> operator%(vec<T, N> const& u, vec<T, N> const& v) {
		vec<T, N> result;
		for (int i = 0; i < N; ++i) {
			result.elements[i] = mod(u.elements[i], v.elements[i]);
		}
		return result;
	}

	template<typename T, int N>
	INLINE bool operator==(const vec<T, N>& u, const vec<T, N>& v) {
		for (int i = 0; i < N; ++i)
			if (u.elements[i] != v.elements[i]) return false;
		return true;
	}

	template<typename T, int N>
	INLINE bool operator!=(const vec<T, N>& u, const vec<T, N>& v) {
		return !(u == v);
	}

#include "Vec2.inl"
#include "Vec3.inl"
#include "Vec4.inl"
}
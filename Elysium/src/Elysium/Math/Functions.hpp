#pragma once

#include "Elysium/Core.h"
#include "Constants.h"

namespace Math {
	/*
	*	TODO: Math utils to add Clamp
	*		Color (lerp between colors, HSV conversion)
	*		deterministic psuedo-random hashes
	*		bezier / spline
	*/

	static bool rand_seeded = false;

#pragma region Trigonometry
	template<typename T>
	INLINE T sin(T x) {
		using M = MathTraits<T>;

		x = mod(x, M::TWO_PI);
		if (x > M::PI)
			x -= M::TWO_PI;
		if (x < -M::PI)
			x += M::TWO_PI;

		if (abs(x) < M::EPSILON)
			return x;

		T x2 = x * x;
		T chain = M::S2 + x2 * (M::S3 + x2 * (M::S4 + x2 * (M::S5 + x2 * (M::S6 + x2 * (M::S7 + x2 * M::S8)))));
		return x + (x * x2) * (M::S1 + x2 * chain);
	}

	template<typename T>
	INLINE T cos(T x) {
		using M = MathTraits<T>;

		x = mod(x, M::TWO_PI);
		if (x > M::PI)
			x -= M::TWO_PI;
		if (x < -M::PI)
			x += M::TWO_PI;

		bool negate = false;
		if (x < -M::PI / static_cast<T>(2)) {
			x = -M::PI - x;
			negate = true; 
		}
		else if (x > M::PI / static_cast<T>(2)) {
			x = PI - x; 
			negate = true; 
		}

		T x2 = x * x;
		T chain = M::C2 + x2 * (M::C3 + x2 * (M::C4 + x2 * (M::C5 + x2 * (M::C6 + x2 * (M::C7 + x2 * M::C8)))));
		T result = static_cast<T>(1) + x2 * (M::C1 + x2 * chain);

		return negate ? -result : result;
	}

	template<typename T>
	INLINE T atan(T x) {
		using M = MathTraits<T>;

		T abs_x = abs(x);
		T result;

		T x2, r;

		if (abs_x <= static_cast <T>(0.66)) {
			x2 = x * x;
			r = M::A1 + x2 * (M::A2 + x2 * (M::A3 + x2 * (M::A4 + x2 * (M::A5 + x2 * (M::A6 + x2 * (M::A7 + x2 * M::A8))))));
			result = x + x * x2 * r;
		}
		else if (abs_x <= static_cast <T>(1.5)) {
			float z = (abs_x - static_cast<T>(1)) / (abs_x + static_cast <T>(1));
			x2 = z * z;
			r = M::A1 + x2 * (M::A2 + x2 * (M::A3 + x2 * (M::A4 + x2 * (M::A5 + x2 * (M::A6 + x2 * (M::A7 + x2 * M::A8))))));
			result = M::PI / static_cast<T>(4) + z + z * x2 * r;
		}
		else {
			float z = static_cast<T>(1) / abs_x;
			x2 = z * z;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = M::PI / static_cast<T>(2) - (z + z * x2 * r);
		}

		return (x < static_cast<T>(0)) ? -result : result;
	}

	template<typename T>
	INLINE T tan(T x) {
		using M = MathTraits<T>;

		T s = sin(x);
		T c = cos(x);
		return (abs(c) < M::EPSILON) ? M::NaN : s / c;
	}

	template<typename T>
	INLINE T asin(T x) {
		using M = MathTraits<T>;

		if (x < -static_cast<T>(1) || x > static_cast<T>(1))
			return M::NaN;
		return atan(x / sqrt(static_cast<T>(1) - x * x));
	}

	template<typename T>
	INLINE T acos(T x) {
		using M = MathTraits<T>;

		if (x < -static_cast<T>(1) || x > static_cast<T>(1))
			return M::NaN;
		return M::HALF_PI - asin(x);
	}

	template<typename T>
	INLINE T csc(T x) {
		using M = MathTraits<T>;

		T s = sin(x);
		return (abs(s) < M::EPSILON) ? M::NaN : static_cast<T>(1) / s;
	}


	template<typename T>
	INLINE T sec(T x) {
		using M = MathTraits<T>;

		T c = cos(x);
		return (abs(c) < M::EPSILON) ? M::NaN : static_cast<T>(1) / c;
	}

	template<typename T>
	INLINE T cot(T x) {
		using M = MathTraits<T>;

		T t = tan(x);
		return (abs(t) < M::EPSILON) ? M::NaN : static_cast<T>(1) / t;
	}

	template<typename T>
	INLINE float degToRad(T degrees) {
		using M = MathTraits<T>;

		return degrees * M::DEG2RAD;
	}

	template<typename T>
	INLINE float radToDeg(T radians) {
		using M = MathTraits<T>;

		return radians * M::RAD2DEG;
	}
#pragma endregion

	template<typename T>
	INLINE float mod(T x, T y) {
		using M = MathTraits<T>;

		if (y == 0.0)
			return M::NaN;
		T quotient = x / y;
		T intPart = (x >= 0.0) ? floor(quotient) : ceil(quotient);
		return x - intPart * y;
	}

	template<typename T>
	INLINE bool isEqualApprox(T x, T y) {
		using M = MathTraits<T>;

		if (x == y)
			return true;
		return abs(x - y) < M::EPSILON * abs(x);
	}

	template<typename T>
	INLINE bool isEqualApprox(T x, T y, T tolerance) {
		if (x == y)
			return true;
		return abs(x - y) < tolerance;
	}

	INLINE float sqrt(float x) {
		if (x <= 0.0f)
			return 0.0f;

		u32 i;
		memcpy(&i, &x, sizeof(i));
		i = (i >> 1) + 0x1FC00000;
		memcpy(&x, &i, sizeof(x));

		x = 0.5f * (x + x / x);
		x = 0.5f * (x + x / x);
		return x;
	}

	INLINE double sqrt(double x) {
		if (x <= 0.0)
			return 0.0;

		u64 i;
		memcpy(&i, &x, sizeof(i));
		i = (i >> 1) + 0x1FF8000000000000ULL;
		memcpy(&x, &i, sizeof(x));

		x = 0.5 * (x + x / x);
		x = 0.5 * (x + x / x);
		x = 0.5 * (x + x / x);
		x = 0.5 * (x + x / x);
		return x;
	}

	INLINE float pow(float x, int exp) {
		float result = 1.0f;
		bool neg = (exp < 0);
		exp = abs(exp);
		while (exp) {
			if (exp & 1)
				result *= x;
			x *= x;
			exp >>= 1;
		}
		return neg ? 1.0f / result : result;
	}

	INLINE int abs(int x) {
		return (x < 0) ? -x : x;
	}

	INLINE float abs(float x) {
		return (x < 0.0f) ? -x : x;
	}

	INLINE double abs(double x) {
		return (x < 0.0) ? -x : x;
	}

	INLINE float floor(float x) {
		float i = (i32)x;
		return (x < 0.0f && x != i) ? i - 1.0f : i;
	}

	INLINE double floor(double x) {
		double i = (i64)x;
		return (x < 0.0 && x != i) ? i - 1 : i;
	}

	INLINE float ceil(float x) {
		float i = (i32)x;
		return (x < 0.0f && x != i) ? i + 1.0f : i;
	}

	INLINE double ceil(double x) {
		double i = (i64)x;
		return (x < 0.0 && x != i) ? i + 1 : i;
	}

	INLINE float min(float x, float y) {
		return x < y ? x : y;
	}

	INLINE double min(double x, double y) {
		return x < y ? x : y;
	}

	INLINE float max(float x, float y) {
		return x > y ? x : y;
	}

	INLINE double max(double x, double y) {
		return x > y ? x : y;
	}

	INLINE float clamp(float x, float minVal, float maxVal) {
		return max(min(x, maxVal), minVal);
	}

	INLINE double clamp(double x, double minVal, double maxVal) {
		return max(min(x, maxVal), minVal);
	}

	/**
	*	@brief Returns true if the value is a power of 2 using bits. 
	*/
	INLINE bool power2(u64 x) {
		return x && !(x & (x - 1));
	}

	// TODO: Impl
	/*
	  i32 random() {
		
	}

	  i32 randomInRange(i32 min, i32 max) {

	}

	  double dRandom() {

	}

	  double dRandomInRange(double min, double max) {

	}
	*/
}
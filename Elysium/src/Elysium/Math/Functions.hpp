#pragma once

#include "Elysium/Core.h"

#include <ctime>
namespace Math {
	/*
	*	TODO: Math utils to add Clamp, Saturate, Min, Max, Step, smoothStep, lerp, inverseLerp,
	*		Noise (perlin, simplex, value noise generations)
	*		Color (lerp between colors, HSV conversion)
	*		nearlyEqual(x, y, epsilon)
	*		deterministic psuedo-random hashes
	*		bezier / spline
	*/
#pragma region Trigonometry
	INLINE ELYSIUM_API float sinf(float x) {
		x = fmod(x, TWO_PI);
		if (x > PI)
			x -= TWO_PI;
		if (x < -PI)
			x += TWO_PI;

		if (fabs(x) < 1.0e-10)
			return x;

		float x2 = x * x;
		float chain = S2 + x2 * (S3 + x2 * (S4 + x2 * (S5 + x2 * (S6 + x2 * (S7 + x2 * S8)))));
		return x + (x * x2) * (S1 + x2 * chain);
	}

	INLINE ELYSIUM_API double sin(double x) {
		x = mod(x, TWO_PI);
		if (x > PI)
			x -= TWO_PI;
		if (x < -PI)
			x += TWO_PI;

		if (fabs(x) < 2.0e-27)
			return x;

		double x2 = x * x;

		if (fabs(x) < 0.3) {
			double r = S2 + x2 * (S3 + x2 * (S4 + x2 * (S5 + x2 * (S6 + x2 * (S7 + x2 * S8)))));
			return x + (x * x2) * (S1 + x2 * r);
		}
		else {
			// Reduce rounding error via compensation
			double qx = (fabs(x) > 0.78125) ? 0.28125 : floor(fabs(x) / 4.0);
			double hz = 0.5 * x2 - qx;
			double a = 1.0 - qx;
			double r = S2 + x2 * (S3 + x2 * (S4 + x2 * (S5 + x2 * (S6 + x2 * (S7 + x2 * S8)))));
			return x + (x * x2) * (S1 + x2 * r); // sin doesn't require correction like cos
		}
	}

	INLINE ELYSIUM_API float cosf(float x) {
		x = fmod(x, TWO_PI);
		if (x > PI)
			x -= TWO_PI;
		if (x < -PI)
			x += TWO_PI;

		bool negate = false;
		if (x < -PI / 2) { 
			x = -PI - x; 
			negate = true; 
		}
		else if (x > PI / 2) { 
			x = PI - x; 
			negate = true; 
		}

		float x2 = x * x;
		float chain = C2 + x2 * (C3 + x2 * (C4 + x2 * (C5 + x2 * (C6 + x2 * (C7 + x2 * C8)))));
		float result = 1.0 + x2 * (C1 + x2 * chain);

		return negate ? -result : result;
	}

	INLINE ELYSIUM_API double cos(double x) {
		x = mod(x, TWO_PI);
		if (x > PI)
			x -= TWO_PI;
		if (x < -PI)
			x += TWO_PI;

		bool negate = false;
		if (x < -PI / 2) {
			x = -PI - x;
			negate = true;
		}
		else if (x > PI / 2) {
			x = PI - x;
			negate = true;
		}

		double r;
		double x2 = x * x;
		
		if (fabs(x) < 0.3) {
			r = C2 + x2 * (C3 + x2 * (C4 + x2 * (C5 + x2 * (C6 + x2 * (C7 + x2 * C8)))));
			return 1.0 - (0.5 * x2 - x2 * r);
		}
		else {
			double qx = (fabs(x) > 0.78125) ? 0.28125 : floor(fabs(x) / 4.0);
			double hz = 0.5 * x2 - qx;
			double a = 1.0 - qx;
			double r = C2 + x2 * (C3 + x2 * (C4 + x2 * (C5 + x2 * (C6 + x2 * (C7 + x2 * C8)))));
			double result = a - (hz - x2 * r);
			return negate ? -result : result;
		}
	}

	INLINE ELYSIUM_API float atanf(float x) {
		float abs_x = fabs(x);
		float result;

		float x2, r;

		if (abs_x <= 0.66f) {
			x2 = x * x;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = x + x * x2 * r;
		}
		else if (abs_x <= 1.5f) {
			float z = (abs_x - 1.0f) / (abs_x + 1.0f);
			x2 = z * z;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = PI / 4.0f + z + z * x2 * r;
		}
		else {
			float z = 1.0f / abs_x;
			x2 = z * z;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = PI / 2.0f - (z + z * x2 * r);
		}

		return (x < 0.0f) ? -result : result;
	}

	INLINE ELYSIUM_API double atan(double x) {
		double abs_x = fabs(x);
		double result;

		double x2, r, z;

		if (abs_x <= 0.66f) {
			x2 = x * x;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = x + x * x2 * r;
		}
		else if (abs_x <= 1.5f) {
			z = (abs_x - 1.0f) / (abs_x + 1.0f);
			x2 = z * z;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = PI / 4.0f + z + z * x2 * r;
		}
		else {
			z = 1.0f / abs_x;
			x2 = z * z;
			r = A1 + x2 * (A2 + x2 * (A3 + x2 * (A4 + x2 * (A5 + x2 * (A6 + x2 * (A7 + x2 * A8))))));
			result = PI / 2.0f - (z + z * x2 * r);
		}

		return (x < 0.0f) ? -result : result;
	}

	INLINE ELYSIUM_API float tanf(float x) {
		float s = sinf(x);
		float c = cosf(x);
		return (fabs(c) < EPSILON) ? NaN : s / c;
	}

	INLINE ELYSIUM_API double tan(double x) {
		double s = sin(x);
		double c = cos(x);
		return (fabs(c) < EPSILON) ? NaN : s / c;
	}

	INLINE ELYSIUM_API float asinf(float x) {
		if (x < -1.0f || x > 1.0f)
			return NaN;
		return atanf(x / sqrtf(1.0 - x * x));
	}

	INLINE ELYSIUM_API double asin(double x) {
		if (x < -1.0 || x > 1.0)
			return NaN;
		return atan(x / sqrt(1.0 - x * x));
	}

	INLINE ELYSIUM_API float acosf(float x) {
		if (x < -1.0 || x > 1.0)
			return NaN;
		return HALF_PI - asinf(x);
	}

	INLINE ELYSIUM_API double acos(double x) {
		if (x < -1.0 || x > 1.0)
			return NaN;
		return HALF_PI - asin(x);
	}

	INLINE ELYSIUM_API float cscf(float x) {
		float s = sinf(x);
		return (fabs(s) < EPSILON) ? NaN : 1.0f / s;
	}

	INLINE ELYSIUM_API double csc(double x) {
		double s = sin(x);
		return (fabs(s) < EPSILON) ? NaN : 1.0 / s;
	}

	INLINE ELYSIUM_API float secf(float x) {
		float c = cosf(x);
		return (fabs(c) < EPSILON) ? NaN : 1.0f / c;
	}

	INLINE ELYSIUM_API double sec(double x) {
		double c = cos(x);
		return (fabs(c) < EPSILON) ? NaN : 1.0 / c;
	}

	INLINE ELYSIUM_API float cotf(float x) {
		float t = tanf(x);
		return (fabs(t) < EPSILON) ? NaN : 1.0f / t;
	}

	INLINE ELYSIUM_API double cot(double x) {
		double t = tan(x);
		return (fabs(t) < EPSILON) ? NaN : 1.0 / t;
	}

	INLINE ELYSIUM_API float degToRad(float degrees) {
		return degrees * DEG2RAD;
	}

	INLINE ELYSIUM_API float radToDeg(float radians) {
		return radians * RAD2DEG;
	}
#pragma endregion

	INLINE ELYSIUM_API float sqrtf(float x) {
		if (x <= 0.0f)
			return 0.0f;

		u32 i;
		memcpy(&i, &x, sizeof(i));
		i = (i >> 1) + 0x1FC00000;
		memcpy(&x, &i, sizeof(x));

		x = 0.5f * (x + x / x);
		x = 0.5f * (x + x / x);
		x = 0.5f * (x + x / x);
		return x;
	}

	INLINE ELYSIUM_API double sqrt(double x) {
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

	INLINE ELYSIUM_API float powf(float x, int exp) {
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

	INLINE ELYSIUM_API float fabs(float x) {
		return (x < 0.0f) ? -x : x;
	}

	INLINE ELYSIUM_API double abs(double x) {
		return (x < 0.0) ? -x : x;
	}

	INLINE ELYSIUM_API double floor(double x) {
		double i = (i64)x;
		return (x < 0.0 && x != i) ? i - 1 : i;
	}

	INLINE ELYSIUM_API double ceil(double x) {
		double i = (i64)x;
		return (x < 0.0 && x != i) ? i + 1 : i;
	}

	INLINE ELYSIUM_API float fmod(float x, float y) {
		if (y == 0.0)
			return NaN;
		float quotient = x / y;
		float intPart = (x >= 0.0) ? floor(quotient) : ceil(quotient);
		return x - intPart * y;
	}

	INLINE ELYSIUM_API double mod(double x, double y) {
		if (y == 0.0)
			return NaN;
		double quotient = x / y;
		double intPart = (x >= 0.0) ? floor(quotient) : ceil(quotient);
		return x - intPart * y;
	}

	/**
	*	@brief Returns true if the value is a power of 2 using bits. 
	*/
	INLINE bool power2(u64 x) {
		return x && !(x & (x - 1));
	}

	ELYSIUM_API i32 random() {

	}

	ELYSIUM_API i32 randomInRange(i32 min, i32 max) {

	}

	ELYSIUM_API double dRandom() {

	}

	ELYSIUM_API double dRandomInRange(double min, double max) {

	}
}
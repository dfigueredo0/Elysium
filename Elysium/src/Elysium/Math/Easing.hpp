#pragma once

#include "Functions.hpp"
#include "Constants.h"

namespace Math {

	template<typename T>
	T easeInQuad(T t) {
		return t * t;
	}

	template<typename T>
	T easeOutQuad(T t) {
		return t * (2 - t);
	}

	template<typename T>
	T easeInOutQuad(T t) {
		return (t < 0.5) ? (2 * t * t) : (-1 + (4 - 2 * t) * t);
	}

	template<typename T>
	T easeInCubic(T t) {
		return t * t * t;
	}

	template<typename T>
	T easeOutCubic(T t) {
		T p = t - 1;
		return p * p * p + 1;
	}

	template<typename T>
	T easeInOutCubic(T t) {
		return (t < 0.5) ? (4 * t * t * t) : ((t - 1) * (2 * t - 2) * (2 * t - 2) + 1);
	}

	template<typename T>
	T easeInSine(T t) {
		using M = MathTraits<T>;
		return static_cast<T>(1) - cos(t * M::HALF_PI);
	}

	template<typename T>
	T easeOutSine(T t) {
		using M = MathTraits<T>;
		return sin(t * M::HALF_PI);
	}

	template<typename T>
	T easeInOutSine(T t) {
		using M = MathTraits<T>;
		return -0.5 * (cos(M::PI * t) - 1);
	}

	template<typename T>
	T easeInExpo(T t) {
		return (t == 0) ? 0 : pow(static_cast<T>(2), 10 * (t - 1));
	}

	template<typename T>
	T easeOutExpo(T t) {
		return (t == 1) ? 1 : static_cast<T>(1) - pow(static_cast<T>(2), -10 * t);
	}

	template<typename T>
	T easeInOutExpo(T t) {
		if (t == 0) return 0;
		if (t == 1) return 1;
		if (t < 0.5) return 0.5 * pow(static_cast<T>(2), 20 * t - 10);
		return 1 - 0.5 * pow(static_cast<T>(2), -20 * t + 10);
	}

	template<typename T>
	T easeInBack(T t) {
		constexpr T c1 = 1.70158;
		constexpr T c3 = c1 + 1;
		return c3 * t * t * t - c1 * t * t;
	}

	template<typename T>
	T easeOutBack(T t) {
		constexpr T c1 = 1.70158;
		constexpr T c3 = c1 + 1;
		T p = t - 1;
		return 1 + c3 * p * p * p + c1 * p * p;
	}

	template<typename T>
	T easeInOutBack(T t) {
		constexpr T c1 = 1.70158;
		constexpr T c2 = c1 * 1.525;
		if (t < 0.5) {
			T p = 2 * t;
			return 0.5 * (p * p * ((c2 + 1) * p - c2));
		}
		else {
			T p = 2 * t - 2;
			return 0.5 * (p * p * ((c2 + 1) * p + c2) + 2);
		}
	}

	template<typename T>
	T bounceEaseIn(T t) {
		return static_cast<T>(1) - bounceEaseOut(static_cast<T>(1) - t);
	}

	template<typename T>
	T bounceEaseOut(T t) {
		if (t < (1 / 2.75)) {
			return 7.5625 * t * t;
		}
		else if (t < (2 / 2.75)) {
			t -= 1.5 / 2.75;
			return 7.5625 * t * t + 0.75;
		}
		else if (t < (2.5 / 2.75)) {
			t -= 2.25 / 2.75;
			return 7.5625 * t * t + 0.9375;
		}
		else {
			t -= 2.625 / 2.75;
			return 7.5625 * t * t + 0.984375;
		}
	}

	template<typename T>
	T bounceEaseInOut(T t) {
		if (t < 0.5) {
			return 0.5 * bounceEaseIn(t * 2);
		}
		else {
			return 0.5 * bounceEaseOut(t * 2 - 1) + 0.5;
		}
	}
}
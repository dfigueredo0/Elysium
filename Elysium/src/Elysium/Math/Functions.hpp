#pragma once

#include "Elysium/Core.h"

namespace Math {
	/*
	*	TODO: Math utils to add Clamp, Saturate, Min, Max, Step, smoothStep, lerp, inverseLerp, slerp, 
	*		Noise (perlin, simplex, value noise generations)
	*		Color (lerp between colors, HSV conversion)
	*		nearlyEqual(x, y, epsilon)
	*		deterministic psuedo-random hashes
	*		bezier / spline
	*/
#pragma region Trigonometry
	INLINE ELYSIUM_API float sin(float x) {

	}

	INLINE ELYSIUM_API double sin(double x) {

	}

	INLINE ELYSIUM_API float cos(float x) {

	}

	INLINE ELYSIUM_API double cos(double x) {

	}

	INLINE ELYSIUM_API float tan(float x) {

	}

	INLINE ELYSIUM_API double tan(double x) {

	}

	INLINE ELYSIUM_API float arcsin(float x) {

	}

	INLINE ELYSIUM_API double arcsin(double x) {

	}

	INLINE ELYSIUM_API float arccos(float x) {

	}

	INLINE ELYSIUM_API double arccos(double x) {

	}

	INLINE ELYSIUM_API float arctan(float x) {

	}

	INLINE ELYSIUM_API double arctan(double x) {

	}

	INLINE ELYSIUM_API float csc(float x) {
	
	}

	INLINE ELYSIUM_API double csc(double x) {
	
	}

	INLINE ELYSIUM_API float sec(float x) {
	
	}

	INLINE ELYSIUM_API double sec(double x) {
	
	}

	INLINE ELYSIUM_API float cot(float x) {
	
	}

	INLINE ELYSIUM_API double cot(double x) {
	
	}
#pragma endregion

	INLINE ELYSIUM_API float fsqrt(float x) {

	}

	INLINE ELYSIUM_API double sqrt(double x) {

	}

	INLINE ELYSIUM_API float pow(float x, int exponent) {

	}

	INLINE ELYSIUM_API float fabs(float x) {

	}

	INLINE ELYSIUM_API double abs(double x) {
		
	}

#pragma region Bitwise Utils
	/**
	*	@brief Returns true if the value is a power of 2 using bits. 
	*/
	INLINE char power2(u64 x) {
		return (x != 0) && ((x & (x - 1)) == 0);
	}
#pragma endregion

	ELYSIUM_API i32 random() {

	}

	ELYSIUM_API i32 randomInRange(i32 min, i32 max) {

	}

	ELYSIUM_API double dRandom() {

	}

	ELYSIUM_API double dRandomInRange(double min, double max) {

	}
}
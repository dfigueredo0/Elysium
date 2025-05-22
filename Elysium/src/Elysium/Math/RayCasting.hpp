#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"
#include "Plane.hpp"

namespace Math {
	template<typename T>
	bool rayIntersectsPlane(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const Plane<T>& plane, T& outT) {
		// implementation stub
	}

	template<typename T>
	bool rayIntersectsAABB(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& boxMin, const vec<T, 3>& boxMax, T& outT) {
		// implementation stub
	}

	template<typename T>
	bool rayIntersectsTriangle(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& v0, const vec<T, 3>& v1, const vec<T, 3>& v2, T& outT) {
		// implementation stub
	}
}
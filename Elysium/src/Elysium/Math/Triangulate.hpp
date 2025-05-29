#pragma once

#include "Elysium/Core.h"
#include "Functions.hpp"
#include "Constants.h"
#include "Vec.hpp"

namespace Math {
	template<typename T>
	struct Triangle { 
		vec<T, 2> v0, v1, v2; 
	};

	template<typename T>
	T edgeFunction(const vec<T, 2>& a, const vec<T, 2>& b, const vec<T, 2>& c) {
		return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	}

	template<typename T>
	bool isPointInTriangle(const vec<T, 2>& pt, const Triangle<T>& tri) {
		T w0 = edgeFunction(tri.v1, tri.v2, pt);
		T w1 = edgeFunction(tri.v2, tri.v0, pt);
		T w2 = edgeFunction(tri.v0, tri.v1, pt);
		return w0 >= 0 && w1 >= 0 && w2 >= 0;
	}

	template<typename T>
	vec<T, 3> computeBarycentricCoords(const vec<T, 2>& p, const Triangle<T>& tri) {
		T area = edgeFunction(tri.v0, tri.v1, tri.v2);
		T w0 = edgeFunction(tri.v1, tri.v2, p);
		T w1 = edgeFunction(tri.v2, tri.v0, p);
		T w2 = edgeFunction(tri.v0, tri.v1, p);
		return vec<T, 3>{ w0 / area, w1 / area, w2 / area };
	}

	template<typename T>
	vec<T, 2> triangleCentroid(const Triangle<T>& tri) {
		return (tri.v0 + tri.v1 + tri.v2) / static_cast<T>(3);
	}

	template<typename T>
	T triangleArea(const Triangle<T>& tri) {
		return static_cast<T>(0.5) * edgeFunction(tri.v0, tri.v1, tri.v2);
	}

	template<typename T>
	bool isDegenerateTriangle(const Triangle<T>& tri) {
		return Math::abs(triangleArea(tri)) < MathTraits<T>::EPSILON;
	}

	template<typename T, typename V>
	V barycentricInterpolate(const V& v0, const V& v1, const V& v2, const vec<T, 3>& bary) {
		return v0 * bary.x + v1 * bary.y + v2 * bary.z;
	}
}
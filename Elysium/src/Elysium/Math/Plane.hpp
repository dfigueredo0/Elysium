#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"

namespace Math {
	template<typename T>
	struct Plane {
		vec<T, 3> normal;
		T distance = 0;

		constexpr Plane(vec<T, 3> normal, T distance) : normal(normal), distance(distance) {}
	};

	template<typename T>
	Plane<T> plane3DCreate(vec<T, 3> v, vec<T, 3> norm) {
		Plane<T> p;
		p.normal = vec3Normalized(norm);
		p.distance = vec3Dot(p.normal, v);

		return p;
	}

	template<typename T>
	void setNorm(vec<T, 3>& norm) {
		;
	}

	template<typename T>
	constexpr INLINE vec<T, 3> getNorm(const Plane<T>* p) {
		return p->normal;
	}

	template<typename T>
	constexpr INLINE vec<T, 3> getCenter(const Plane<T>* p) {
		return p->normal * p->distance;
	}

	template<typename T>
	vec<T, 3> projectPoint(const Plane<T>& plane, const vec<T, 3>& point) {

	}

	template<typename T>
	Plane<T> transformPlane(const Plane<T>& plane, const Matrix<T, 4, 4>& transform) {

	}

	template<typename T>
	ELYSIUM_API T signedDistance(const Plane<T>* p, const vec<T, 3>* position) {

	}

	template<typename T>
	ELYSIUM_API bool intersectPlanes() {

	}

	template<typename T>
	ELYSIUM_API bool intersectSphere(const Plane<T>* p, const vec<T, 3>* center, T radius) {

	}

	template<typename T>
	ELYSIUM_API bool intersectsAABB(const Plane<T>* p, const vec<T, 3>* center, const vec<T, 3>* extents) {

	}

	template<typename T>
	ELYSIUM_API bool intersectRay() {

	}

	template<typename T>
	ELYSIUM_API bool intersectSegment() {

	}
}
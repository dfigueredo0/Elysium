#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"
#include "AABB.hpp"

namespace Math {
	template<typename T>
	struct Plane {
		vec<T, 3> normal;
		T distance = 0;

		constexpr Plane() = default;
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
		norm = vec3Normalized(norm);
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
		T d = vec3Dot(plane.normal, point) - plane.distance;
		return point - plane.normal * d;
	}

	template<typename T>
	Plane<T> transformPlane(const Plane<T>& plane, const Matrix<T, 4, 4>& transform) {
		vec<T, 4> n4 = vec4FromVec3(plane.normal, plane.distance);
		n4 = vec4MulMat4(transform, n4);
		Plane<T> result;
		result.normal = vec3Normalized(vec3FromVec4(n4));
		result.distance = n4.w / vec3Length(result.normal);
		return result;
	}

	template<typename T>
	  T signedDistance(const Plane<T>* p, const vec<T, 3>* position) {
		return vec3Dot(p->normal, *position) - p->distance;
	}

	template<typename T>
	  bool intersectPlanes() {
		// Placeholder; proper implementation requires 3-plane intersection logic
		return false;
	}

	template<typename T>
	  bool intersectSphere(const Plane<T>* p, const vec<T, 3>* center, T radius) {
		T dist = signedDistance(p, center);
		return Math::abs(dist) <= radius;
	}

	template<typename T>
	  bool intersectsAABB(const Plane<T>* p, const AABB<T>& box) {
		vec<T, 3> center = box.center();
		vec<T, 3> extents = box.size() * static_cast<T>(0.5);
		vec<T, 3> absN = vec<T, 3>{ Math::abs(p->normal.x), Math::abs(p->normal.y), Math::abs(p->normal.z) };
		T r = vec3Dot(absN, extents);
		T s = signedDistance(p, &center);
		return Math::abs(s) <= r;
	}

	template<typename T>
	  bool intersectRay(const Plane<T>* p, const vec<T, 3>* origin, const vec<T, 3>* dir, T& tOut) {
		T denom = vec3Dot(p->normal, *dir);
		if (Math::abs(denom) < MathTraits<T>::EPSILON) return false;
		tOut = (p->distance - vec3Dot(p->normal, *origin)) / denom;
		return tOut >= 0;
	}

	template<typename T>
	  bool intersectSegment(const Plane<T>* p, const vec<T, 3>* a, const vec<T, 3>* b, vec<T, 3>& outPoint) {
		vec<T, 3> ab = *b - *a;
		T denom = vec3Dot(p->normal, ab);
		if (Math::abs(denom) < MathTraits<T>::EPSILON) return false;
		T t = (p->distance - vec3Dot(p->normal, *a)) / denom;
		if (t < 0 || t > 1) return false;
		outPoint = *a + ab * t;
		return true;
	}
}
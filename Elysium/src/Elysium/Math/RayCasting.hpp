#pragma once

#include "Elysium/Core.h"
#include "Constants.h"
#include "Vec.hpp"
#include "Matrix.hpp"
#include "Plane.hpp"
#include "AABB.hpp"

namespace Math {
	template<typename T>
	bool rayIntersectsPlane(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const Plane<T>& plane, T& outT) {
		T denom = vec3Dot(plane.normal, rayDir);
		if (Math::abs(denom) < MathTraits<T>::EPSILON) return false;
		outT = (plane.distance - vec3Dot(plane.normal, rayOrigin)) / denom;
		return outT >= 0;
	}

	template<typename T>
	bool rayIntersectsAABB(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const AABB<T>& box, T& outT) {
		const vec<T, 3>& boxMin = box.min;
		const vec<T, 3>& boxMax = box.max;

		T tMin = (boxMin.x - rayOrigin.x) / rayDir.x;
		T tMax = (boxMax.x - rayOrigin.x) / rayDir.x;
		if (tMin > tMax) std::swap(tMin, tMax);

		T tyMin = (boxMin.y - rayOrigin.y) / rayDir.y;
		T tyMax = (boxMax.y - rayOrigin.y) / rayDir.y;
		if (tyMin > tyMax) std::swap(tyMin, tyMax);

		if ((tMin > tyMax) || (tyMin > tMax)) return false;
		tMin = Math::max(tMin, tyMin);
		tMax = Math::min(tMax, tyMax);

		T tzMin = (boxMin.z - rayOrigin.z) / rayDir.z;
		T tzMax = (boxMax.z - rayOrigin.z) / rayDir.z;
		if (tzMin > tzMax) std::swap(tzMin, tzMax);

		if ((tMin > tzMax) || (tzMin > tMax)) return false;
		tMin = Math::max(tMin, tzMin);
		tMax = Math::min(tMax, tzMax);

		outT = tMin >= 0 ? tMin : tMax;
		return outT >= 0;
	}

	template<typename T>
	bool rayIntersectsTriangle(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& v0, const vec<T, 3>& v1, const vec<T, 3>& v2, T& outT) {
		vec<T, 3> edge1 = v1 - v0;
		vec<T, 3> edge2 = v2 - v0;
		vec<T, 3> h = vec3Cross(rayDir, edge2);
		T a = vec3Dot(edge1, h);
		if (Math::abs(a) < MathTraits<T>::EPSILON) return false;

		T f = static_cast<T>(1) / a;
		vec<T, 3> s = rayOrigin - v0;
		T u = f * vec3Dot(s, h);
		if (u < 0.0 || u > 1.0) return false;

		vec<T, 3> q = vec3Cross(s, edge1);
		T v = f * vec3Dot(rayDir, q);
		if (v < 0.0 || u + v > 1.0) return false;

		outT = f * vec3Dot(edge2, q);
		return outT >= 0;
	}

	template<typename T>
	bool rayIntersectsSphere(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& sphereCenter, T radius, T& outT) {
		vec<T, 3> m = rayOrigin - sphereCenter;
		T b = vec3Dot(m, rayDir);
		T c = vec3Dot(m, m) - radius * radius;
		if (c > 0 && b > 0) return false;
		T discr = b * b - c;
		if (discr < 0) return false;
		outT = -b - Math::sqrt(discr);
		return outT >= 0;
	}


	template<typename T>
	vec<T, 3> closestPointOnRay(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& point) {
		T t = vec3Dot(point - rayOrigin, rayDir);
		return rayOrigin + rayDir * t;
	}

	template<typename T>
	T raySegmentDistance(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& segA, const vec<T, 3>& segB, T& outRayT, T& outSegT) {
		vec<T, 3> u = rayDir;
		vec<T, 3> v = segB - segA;
		vec<T, 3> w0 = rayOrigin - segA;
		T a = vec3Dot(u, u);
		T b = vec3Dot(u, v);
		T c = vec3Dot(v, v);
		T d = vec3Dot(u, w0);
		T e = vec3Dot(v, w0);
		T denom = a * c - b * b;

		if (Math::abs(denom) < MathTraits<T>::EPSILON) {
			outRayT = outSegT = 0;
			return vec3Length(w0);
		}

		outRayT = (b * e - c * d) / denom;
		outSegT = (a * e - b * d) / denom;
		vec<T, 3> closestRay = rayOrigin + u * outRayT;
		vec<T, 3> closestSeg = segA + v * outSegT;
		return vec3Length(closestRay - closestSeg);
	}

	template<typename T>
	bool rayIntersectsOBB(const vec<T, 3>& rayOrigin, const vec<T, 3>& rayDir, const vec<T, 3>& obbCenter, const Matrix<T, 3, 3>& axes, const vec<T, 3>& halfExtents, T& outT) {
		T tMin = 0;
		T tMax = std::numeric_limits<T>::max();
		vec<T, 3> p = obbCenter - rayOrigin;

		for (int i = 0; i < 3; ++i) {
			vec<T, 3> axis = vec<T, 3>{ axes(i,0), axes(i,1), axes(i,2) };
			T e = vec3Dot(axis, p);
			T f = vec3Dot(axis, rayDir);

			if (Math::abs(f) > MathTraits<T>::EPSILON) {
				T t1 = (e + halfExtents[i]) / f;
				T t2 = (e - halfExtents[i]) / f;
				if (t1 > t2) std::swap(t1, t2);
				tMin = Math::max(tMin, t1);
				tMax = Math::min(tMax, t2);
				if (tMin > tMax) return false;
			}
			else if (-e - halfExtents[i] > 0 || -e + halfExtents[i] < 0) {
				return false;
			}
		}
		outT = tMin;
		return true;
	}
}
#pragma once

#include "Elysium/Core.h"
#include "Functions.hpp"
#include "Vec.hpp"

namespace Math {
	template<typename T>
	struct AABB {
		vec<T, 3> min;
		vec<T, 3> max;

		bool intersects(const AABB<T>& other) const {
			return (min.x <= other.max.x && max.x >= other.min.x) &&
				(min.y <= other.max.y && max.y >= other.min.y) &&
				(min.z <= other.max.z && max.z >= other.min.z);
		}

		bool containsPoint(const vec<T, 3>& point) const {
			return (point.x >= min.x && point.x <= max.x) &&
				(point.y >= min.y && point.y <= max.y) &&
				(point.z >= min.z && point.z <= max.z);
		}

		vec<T, 3> center() const {
			return (min + max) * static_cast<T>(0.5);
		}

		vec<T, 3> size() const {
			return max - min;
		}
	};

	template<typename T, int N>
	struct Shape {
		vec<T, N>* points;
		i32 count;
	};

	template<typename T>
	AABB<T> merge(const AABB<T>& a, const AABB<T>& b) {
		return AABB<T>{
			.min = vec<T, 3>(
				Math::min(a.min.x, b.min.x),
				Math::min(a.min.y, b.min.y),
				Math::min(a.min.z, b.min.z)),
				.max = vec<T, 3>(
					Math::max(a.max.x, b.max.x),
					Math::max(a.max.y, b.max.y),
					Math::max(a.max.z, b.max.z))
		};
	}

	template<typename T, int N>
	vec<T, N> support(const Shape<T, N>& shape1, const Shape<T, N>& shape2, const vec<T, N>& dir) {
		vec<T, N> p1 = shape1.points[0];
		T max1 = dot(p1, dir);
		for (i32 i = 1; i < shape1.count; ++i) {
			T d = dot(shape1.points[i], dir);
			if (d > max1) {
				max1 = d;
				p1 = shape1.points[i];
			}
		}

		vec<T, N> p2 = shape2.points[0];
		T max2 = dot(p2, -dir);
		for (i32 i = 1; i < shape2.count; ++i) {
			T d = dot(shape2.points[i], -dir);
			if (d > max2) {
				max2 = d;
				p2 = shape2.points[i];
			}
		}

		return p1 - p2;
	}

	template<typename T, int N>
	bool nextSimplex(vec<T, N>* simplex, i32& count, vec<T, N>& dir) {
		if constexpr (N == 2) {
			if (count == 2) {
				vec<T, 2> a = simplex[1];
				vec<T, 2> b = simplex[0];
				vec<T, 2> ab = b - a;
				vec<T, 2> ao = -a;
				dir = vec<T, 2>{ ab.y, -ab.x };
				if (dot(dir, ao) < 0) dir = -dir;
				return false;
			}
			else if (count == 3) {
				vec<T, 2> a = simplex[2];
				vec<T, 2> b = simplex[1];
				vec<T, 2> c = simplex[0];
				vec<T, 2> ab = b - a;
				vec<T, 2> ac = c - a;
				vec<T, 2> ao = -a;

				vec<T, 2> abPerp = vec<T, 2>{ ab.y, -ab.x };
				if (dot(abPerp, ao) > 0) {
					simplex[0] = b;
					simplex[1] = a;
					count = 2;
					dir = abPerp;
					return false;
				}
				else {
					simplex[1] = c;
					simplex[2] = a;
					count = 2;
					dir = vec<T, 2>{ -ac.y, ac.x };
					if (dot(dir, ao) < 0) dir = -dir;
					return false;
				}
			}
		}
		else if constexpr (N == 3) {
			if (count == 2) {
				vec<T, 3> a = simplex[1];
				vec<T, 3> b = simplex[0];
				vec<T, 3> ab = b - a;
				vec<T, 3> ao = -a;
				dir = cross(cross(ab, ao), ab);
				return false;
			}
			else if (count == 3) {
				vec<T, 3> a = simplex[2];
				vec<T, 3> b = simplex[1];
				vec<T, 3> c = simplex[0];
				vec<T, 3> ab = b - a;
				vec<T, 3> ac = c - a;
				vec<T, 3> ao = -a;
				vec<T, 3> abc = cross(ab, ac);

				vec<T, 3> abp = cross(abc, ab);
				if (dot(abp, ao) > 0) {
					simplex[0] = b;
					simplex[1] = a;
					count = 2;
					dir = cross(cross(ab, ao), ab);
					return false;
				}

				vec<T, 3> acp = cross(ac, abc);
				if (dot(acp, ao) > 0) {
					simplex[0] = c;
					simplex[1] = a;
					count = 2;
					dir = cross(cross(ac, ao), ac);
					return false;
				}

				dir = abc;
				if (dot(abc, ao) < 0) dir = -dir;
				return false;
			}
			else if (count == 4) {
				return true;
			}
		}
		return false;
	}

	template<typename T, int N>
	bool GJKIntersect(const Shape<T, N>& shape1, const Shape<T, N>& shape2) {
		vec<T, N> dir;
		dir.elements[0] = static_cast<T>(1);
		for (int i = 1; i < N; ++i) dir.elements[i] = static_cast<T>(0);

		vec<T, N> simplex[4];
		i32 count = 0;
		simplex[count++] = support(shape1, shape2, dir);
		dir = -simplex[0];

		while (true) {
			vec<T, N> newPoint = support(shape1, shape2, dir);
			if (dot(newPoint, dir) <= static_cast<T>(0))
				return false;

			simplex[count++] = newPoint;
			if (nextSimplex(simplex, count, dir))
				return true;
		}
	}
}
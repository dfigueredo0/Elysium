#pragma once

/*
* SAT and/or GJK algorithm
* SAT only works for convex polygons
*		Any line made by two points within the polygon will also be within the polygon
*		All internal angles are less than 180 degrees
* GJK works with both <- should impl this one better and faster
* 
* 
* For SAT algo:
* 
* separation > 0: no collision
* separation < 0: collision
* float FindMinSeparation(shape& a, shape& b) {
*	float separation = std::numeric_limits<float>::lowest()
*	for (Vec2 va : a->vertices) {
*		Vec2 norm = a->Perpendicular(va);
*		float minSep = std::numeric_limits<float>::max();
*		for (Vec2 vb : b->vertices) {
*			minSep = std::min(minSep, Dot(vb - va, normal));
*		}
*		if (minSep > seperation) 
*			separation = minSep;
*	}
*	return separation;
* }
* 
* bool IsColliding(shape& a, shape& b) {
*	return FindMinSeparation(a, b) <= 0 && FindMinSeparation(b, a) <= 0;
* } 
*/

namespace Math {
	template<typename T>
	struct AABB {
		vec<T, 3> min;
		vec<T, 3> max;

		bool intersects(const AABB<T>& other) const {

		}

		bool containsPoint(const vec<T, 3>& point) const {

		}

		vec<T, 3> center() const {

		}

		vec<T, 3> size() const {

		}
	};

	template<typename T>
	bool GJKIntersect(const AABB<T>& a, const AABB<T>& b) { // placeholder
		
	}
}
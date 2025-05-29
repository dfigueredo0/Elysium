#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"
#include "Plane.hpp"
#include "Projection.hpp"
#include "AABB.hpp"

namespace Math {
	template<typename T>
	struct Frustum {
		Plane<T> sides[6];

		constexpr Frustum(const vec<T, 3>* position, const vec<T, 3>* forward, const vec<T, 3>* right, const vec<T, 3>* up, 
			T aspect, T fov, T near, T far) 
		{
					
		}
	};

	template<typename T>
	Frustum<T> frustomCreate(const vec<T, 3>& position, const vec<T, 3>& forward, const vec<T, 3>& right, const vec<T, 3>& up,
		T aspect, T fov, T near, T far) {
		Frustum<T> f;

		T halfV = far * tan(fov * static_cast<T>(0.5));
		T halfH = halfV * aspect;
		vec<T, 3> fwd = forward;
		vec<T, 3> fwdFar = fwd * far;

		f.sides[0] = plane3DCreate(((fwd * near) + position), fwd);
		f.sides[1] = plane3DCreate((position + fwdFar) + (fwd * -static_cast<T>(1)));
		f.sides[2] = plane3DCreate(position, vec3Cross(up, (fwdFar + (right * halfH))));
		f.sides[3] = plane3DCreate(position, vec3Cross((fwdFar - (right * halfH)), up));
		f.sides[4] = plane3DCreate(position, vec3Cross(right, (fwdFar - (up * halfV))));
		f.sides[5] = plane3DCreate(position, vec3Cross((fwdFar + (up * halfV)), right));
		
		return f;
	}

	template<typename T>
	bool containsPoint(const Frustum<T>& frustum, const vec<T, 3>& point) {
		for (int i = 0; i < 6; ++i) {
			if (signedDistance(&frustum.sides[i], &point) < 0)
				return false;
		}
		return true;
	}

	template<typename T>
	  bool intersectsSphere(const Frustum<T>* f, const vec<T, 3>* center, T radius) {
		for (int i = 0; i < 6; ++i) {
			T dist = signedDistance(&f->sides[i], center);
			if (dist < -radius)
				return false;
		}
		return true;
	}

	template<typename T>
	  bool intersectsAABB(const Frustum<T>* f, const AABB<T>& box) {
		for (int i = 0; i < 6; ++i) {
			if (!intersectsAABB(&f->sides[i], box))
				return false;
		}
		return true;
	}
}
}
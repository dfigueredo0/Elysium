#pragma once

#include "Elysium/Core.h"
#include "Matrix.hpp"
#include "Functions.hpp"
#include "Vec.hpp"

namespace Math {
	/** 
	*   @brief Creates and returns an orthographc projection matrix. Typically used to render flat or 2D scenes.
	*/
	template<typename T>
	INLINE Matrix<T, 4, 4> orthographic(T left, T right, T bottom, T top, T zNear = T(-1), T zFar = T(1)) {
		Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();

		T rl = static_cast<T>(1) / (right - left);
		T tb = static_cast<T>(1) / (top - bottom);
		T fn = static_cast<T>(1) / (zFar - zNear);

		mat(0, 0) = static_cast<T>(2) * rl;
		mat(1, 1) = static_cast<T>(2) * tb;
		mat(2, 2) = static_cast<T>(-2) * fn;

		mat(0, 3) = -(right + left) * rl;
		mat(1, 3) = -(top + bottom) * tb;
		mat(2, 3) = -(zFar + zNear) * fn;

		return mat;
	}

	/** 
	*   @brief Creates and returns a perspective matric. Typically used to render 3d scenes.
	* 
	*	@param fov The field of view in radians.
	*	@param aspect The aspect ratio, height of screen / width of screen.
	*	@param near The near clipping plane distance
	*	@param far The far clipping plane distance
	*/
	template<typename T>
	INLINE Matrix<T, 4, 4> perspective(T fov, T aspect, T zNear, T zFar) {
		Matrix<T, 4, 4> mat = Math::identity<T, 4, 4>();

		mat.data[0] = aspect * (Math::cot(fov / static_cast<T>(2)));
		mat.data[5] = Math::cot(fov / 2);
		mat.data[10] = zFar / (zFar - zNear);
		mat.data[11] = static_cast<T>(1);
		mat.data[14] = -((static_cast<T>(2) * zFar * zNear) / (zFar - zNear));

		return mat;
	}


	/**
	*	@brief Creates and returns a look-at matrix.
	* 
	*	@param pos The position of the actor.
	*	@param target The target to "look at".
	*	@param up The up vector.
	*	@return a matrix looking at the target from the perspective of their position.
	*/
	template<typename T>
	INLINE Matrix<T, 4, 4> lookAt(const vec<T, 3>& pos, const vec<T, 3>& target, const vec<T, 3>& up) {
		Matrix<T, 4, 4> mat;
		vec<T, 3> forward = Math::vec3Normalized((target - pos));
		vec<T, 3> right = Math::vec3Normalized(vec3Cross(forward, up));
		vec<T, 3> u = Math::vec3Cross(right, forward);

		mat.setRow(0, vec<T, 4>(right.x, right.y, right.z, -Math::vec3Dot(right, pos)));
		mat.setRow(1, vec<T, 4>(u.x, u.y, u.z, -vec3Dot(u, pos)));  // fixed
		mat.setRow(2, vec<T, 4>(-forward.x, -forward.y, -forward.z, vec3Dot(forward, pos)));
		mat.setRow(3, vec<T, 4>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)));

		return mat;
	}
}
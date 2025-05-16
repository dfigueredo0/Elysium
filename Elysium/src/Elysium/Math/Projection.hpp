#pragma once

#include "Elysium/Core.h"
#include "Matrix.hpp"
#include "Functions.hpp"
#include "Vec3.hpp"

namespace Math {
	/** 
	*   @brief Creates and returns an orthographc projection matrix. Typically used to render flat or 2D scenes.
	*/
	INLINE mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 mat = mat4::identity();

		float lr = 1.0f / (left - right);
		float bt = 1.0f / (bottom - top);
		float nf = 1.0f / (near - far);

		mat.data[0] = -2.0f * lr;
		mat.data[5] = -2.0f * bt;
		mat.data[10] = -2.0f * nf;

		mat.data[12] = (left + right) * lr;
		mat.data[13] = (top + bottom) * bt;
		mat.data[14] = (far + near) * nf;

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
	INLINE mat4 perspective(float fov, float aspect, float near, float far) {
		mat4 mat = mat4::identity();

		mat.data[0] = aspect * (cot(fov / 2));
		mat.data[5] = cot(fov / 2);
		mat.data[10] = far / (far - near);
		mat.data[11] = 1.0f;
		mat.data[14] = -((2.0f * far * near) / (far - near));

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
	INLINE mat4 lookAt(const vec3& pos, const vec3& target, const vec3& up) {
		mat4 mat;
		vec3 forward = vec3Normalized(vec3Sub(target, pos));
		vec3 right = vec3Normalized(vec3Cross(forward, up));
		vec3 u = vec3Cross(right, forward);

		mat.setRow(0, vec4(right.x, right.y, right.z, -vec3Dot(right, pos)));
		mat.setRow(1, vec4(u.x, u.y, u.z, -vec3Dot(u, pos)));
		mat.setRow(2, vec4(-forward.x, -forward.y, -forward.z, vec3Dot(forward, pos)));
		mat.setRow(3, vec4(0.0f, 0.0f, 0.0f, 1.0f));

		return mat;
	}
}
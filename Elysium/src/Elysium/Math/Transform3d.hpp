#pragma once

#include "Elysium/Core.h"
#include "Matrix.hpp"
#include "Vec.hpp"
#include "Quaternion.hpp"

namespace Math {
	template<typename T>
	struct Transform3D {
		Matrix<T, 4, 4> local;
		vec<T, 3> position;
		quat<T> rotation;
		vec<T, 3> scale;
		bool dirty;

		struct Transform3D* parent;

		constexpr Transform3D()
			: local(Matrix<T, 4, 4>::identity()),
			position(vec3Zero<T>()),
			rotation(quat<T>::identity()),
			scale(vec3One<T>()),
			dirty(false),
			parent(nullptr)
		{
		}
	};

	template<typename T>
	ELYSIUM_API void invert() {

	}

	template<typename T>
	ELYSIUM_API void affineInvert() {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> inverse() {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> affineInverse() {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> lookAt() {

	}

	template<typename T>
	ELYSIUM_API quat<T> getForward() {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> transformFromPosition(vec<T, 3> position) {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> transformFromRotation(quat<T> rotation) {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> transformFromPositionRotation(vec<T, 3> position, quat<T> rotation) {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> transformFromPositionRotationScale(vec<T, 3> position, quat<T> rotation, vec<T, 3> scale) {

	}

	template<typename T>
	ELYSIUM_API void translate(Transform3D<T>* transform, vec<T, 3> translation) {

	}

	template<typename T>
	ELYSIUM_API void rotate(Transform3D<T>* transform, quat<T> rotation) {

	}

	template<typename T>
	ELYSIUM_API void scale(Transform3D<T>* transform, vec<T, 3> scale) {

	}

	template<typename T>
	ELYSIUM_API Transform3D<T> getParent(Transform3D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setParent(Transform3D<T>* transform, Transform3D<T>* parent) {

	}

	template<typename T>
	ELYSIUM_API vec<T, 3> getPosition(const Transform3D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setPosition(Transform3D<T>* transform, vec<T, 3> position) {

	}

	template<typename T>
	ELYSIUM_API quat<T> getRotation(const Transform3D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setRotation(Transform3D<T>* transform, quat<T> rotation) {

	}

	template<typename T>
	ELYSIUM_API vec<T, 3> getScale(const Transform3D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setScale(Transform3D<T>* transform, vec<T, 3> scale) {

	}

	template<typename T>
	ELYSIUM_API void markDirty(Transform3D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API Matrix<T, 4, 4> getLocal(Transform3D<T>* transform) {
		if (transform) {
			if (transform->dirty) {
				Matrix<T, 4, 4> mat = quatToMat4(transform->rotation) * mat4Translation(transform->position);
				mat = mat4Scale(transform->scale) * mat;
				transform->dirty = false;
			}
			return transform->local = mat;
		}
		return Matrix<T, 4, 4>::identity();
	}

	template<typename T>
	ELYSIUM_API Matrix<T, 4, 4> getWorld(Transform3D<T>* transform) {
		if (transform) {
			Matrix<T, 4, 4> local = getLocal(transform);
			if (transform->parent) {
				Matrix<T, 4, 4> parent = getWorld(transform->parent);
				return local * parent;
			}
			return local;
		}
		return Matrix<T, 4, 4>::identity();
	}

	using Transform3Df = Transform3D<float>;
	using Transform3Dd = Transform3D<double>;
}
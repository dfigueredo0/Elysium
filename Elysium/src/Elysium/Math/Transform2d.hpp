#pragma once

#include "Elysium/Core.h"
#include "Vec.hpp"
#include "Matrix.hpp"

namespace Math {
	template<typename T>
	struct Transform2D {
		Matrix<T, 3, 3> local;
		vec<T, 2> position;
		vec<T, 3> rotation;
		vec<T, 2> scale;
		bool dirty;

		struct Transform2D* parent;

		constexpr Transform2D()
			: local(Matrix<T, 3, 3>::identity()),
			position(vec2Zero<T>()),
			rotation(vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)),
			scale(vec2One<T>()),
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
	ELYSIUM_API Transform2D<T> inverse() {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> affineInverse() {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> transformFromPosition(vec<T, 2> position) {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> transformFromRotation(vec<T, 3> rotation) {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> transformFromPositionRotation(vec<T, 2> position, vec<T, 3> rotation) {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> transformFromPositionRotationScale(vec<T, 2> position, vec<T, 3> rotation, vec<T, 2> scale) {

	}

	template<typename T>
	ELYSIUM_API void translate(Transform2D<T>* transform, vec<T, 2> translation) {

	}

	template<typename T>
	ELYSIUM_API void rotate(Transform2D<T>* transform, vec<T, 3> rotation) {

	}

	template<typename T>
	ELYSIUM_API void scale(Transform2D<T>* transform, vec<T, 2> scale) {

	}

	template<typename T>
	ELYSIUM_API Transform2D<T> getParent(Transform2D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setParent(Transform2D<T>* transform, Transform2D<T>* parent) {

	}

	template<typename T>
	ELYSIUM_API vec<T, 3> getPosition(const Transform2D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setPosition(Transform2D<T>* transform, vec<T, 2> position) {

	}

	template<typename T>
	ELYSIUM_API vec<T, 3> getRotation(const Transform2D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setRotation(Transform2D<T>* transform, vec<T, 3> rotation) {

	}

	template<typename T>
	ELYSIUM_API vec<T, 3> getScale(const Transform2D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API void setScale(Transform2D<T>* transform, vec<T, 2> scale) {

	}

	template<typename T>
	ELYSIUM_API void markDirty(Transform2D<T>* transform) {

	}

	template<typename T>
	ELYSIUM_API Matrix<T, 3, 3> getLocal(Transform2D<T>* transform) {
		if (transform) {
			if (transform->dirty) {
				Matrix<T, 3, 3> mat = vec3ToMat3(transform->rotation) * mat3Translation(transform->position);
				mat = mat3Scale(transform->scale) * mat;
				transform->dirty = false;
			}
			return transform->local = mat;
		}
		return Matrix<T, 3, 3>::identity();
	}

	template<typename T>
	ELYSIUM_API Matrix<T, 3, 3> getWorld(Transform2D<T>* transform) {
		if (transform) {
			Matrix<T, 3, 3> local = getLocal(transform);
			if (transform->parent) {
				Matrix<T, 3, 3> parent = getWorld(transform->parent);
				return local * parent;
			}
			return local;
		}
		return Matrix<T, 3, 3>::identity();
	}

	using Transform2Df = Transform2D<float>;
	using Transform2Dd = Transform2D<double>;
}
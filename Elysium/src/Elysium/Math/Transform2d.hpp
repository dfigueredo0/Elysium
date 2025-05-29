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
	  void markDirty(Transform2D<T>* transform) {
		transform->dirty = true;
	}

	template<typename T>
	  void invert(Transform2D<T>* t) {
		t->local = getInverse(t->local);
		t->position = -t->position;
		t->scale = vec2One<T>() / t->scale;
		markDirty(t);
	}

	template<typename T>
	  void affineInvert(Transform2D<T>* t) {
		t->local = mat3AffineInverse(t->local);
		markDirty(t);
	}

	template<typename T>
	  Transform2D<T> inverse(const Transform2D<T>& t) {
		Transform2D<T> result = t;
		invert(&result);
		return result;
	}

	template<typename T>
	  Transform2D<T> affineInverse(const Transform2D<T>& t) {
		Transform2D<T> result = t;
		affineInvert(&result);
		return result;
	}

	template<typename T>
	  Transform2D<T> transformFromPosition(vec<T, 2> position) {
		Transform2D<T> t;
		t.position = position;
		markDirty(&t);
		return t;
	}

	template<typename T>
	  Transform2D<T> transformFromRotation(vec<T, 3> rotation) {
		Transform2D<T> t;
		t.rotation = rotation;
		markDirty(&t);
		return t;
	}

	template<typename T>
	  Transform2D<T> transformFromPositionRotation(vec<T, 2> position, vec<T, 3> rotation) {
		Transform2D<T> t;
		t.position = position;
		t.rotation = rotation;
		markDirty(&t);
		return t;
	}

	template<typename T>
	  Transform2D<T> transformFromPositionRotationScale(vec<T, 2> position, vec<T, 3> rotation, vec<T, 2> scale) {
		Transform2D<T> t;
		t.position = position;
		t.rotation = rotation;
		t.scale = scale;
		markDirty(&t);
		return t;
	}

	template<typename T>
	  void translate(Transform2D<T>* transform, vec<T, 2> translation) {
		transform->position += translation;
		markDirty(transform);
	}

	template<typename T>
	  void rotate(Transform2D<T>* transform, vec<T, 3> rotation) {
		transform->rotation = rotation;
		markDirty(transform);
	}

	template<typename T>
	  void scale(Transform2D<T>* transform, vec<T, 2> scale) {
		transform->scale *= scale;
		markDirty(transform);
	}

	template<typename T>
	  Transform2D<T> getParent(Transform2D<T>* transform) {
		return transform->parent ? *transform->parent : Transform2D<T>();
	}

	template<typename T>
	  void setParent(Transform2D<T>* transform, Transform2D<T>* parent) {
		transform->parent = parent;
		markDirty(transform);
	}

	template<typename T>
	  vec<T, 2> getPosition(const Transform2D<T>* transform) {
		return transform->position;
	}

	template<typename T>
	  void setPosition(Transform2D<T>* transform, vec<T, 2> position) {
		transform->position = position;
		markDirty(transform);
	}

	template<typename T>
	  vec<T, 3> getRotation(const Transform2D<T>* transform) {
		return transform->rotation;
	}

	template<typename T>
	  void setRotation(Transform2D<T>* transform, vec<T, 3> rotation) {
		transform->rotation = rotation;
		markDirty(transform);
	}

	template<typename T>
	  vec<T, 2> getScale(const Transform2D<T>* transform) {
		return transform->scale;
	}

	template<typename T>
	  void setScale(Transform2D<T>* transform, vec<T, 2> scale) {
		transform->scale = scale;
		markDirty(transform);
	}

	template<typename T>
	  Matrix<T, 3, 3> getLocal(Transform2D<T>* transform) {
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
	  Matrix<T, 3, 3> getWorld(Transform2D<T>* transform) {
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
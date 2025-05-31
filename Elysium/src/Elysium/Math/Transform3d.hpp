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
	void invert(Transform3D<T>* t) {
		t->local = getInverse(t->local);
		t->position = -t->position;
		t->rotation = quatInverse(t->rotation);
		t->scale = vec3One<T>() / t->scale;
		t->dirty = true;
	}

	template<typename T>
	void affineInvert(Transform3D<T>* t) {
		t->local = mat4AffineInverse(t->local);
		t->dirty = true;
	}

	template<typename T>
	Transform3D<T> inverse(const Transform3D<T>& t) {
		Transform3D<T> result = t;
		invert(&result);
		return result;
	}

	template<typename T>
	Transform3D<T> affineInverse(const Transform3D<T>& t) {
		Transform3D<T> result = t;
		affineInvert(&result);
		return result;
	}

	template<typename T>
	Transform3D<T> lookAt(const vec<T, 3>& from, const vec<T, 3>& to, const vec<T, 3>& up) {
		Transform3D<T> t;
		vec<T, 3> forward = vec3Normalized(to - from);
		vec<T, 3> right = vec3Normalized(vec3Cross(up, forward));
		vec<T, 3> upDir = vec3Cross(forward, right);
		Matrix<T, 3, 3> basis;
		basis(0, 0) = right.x; basis(0, 1) = upDir.x; basis(0, 2) = forward.x;
		basis(1, 0) = right.y; basis(1, 1) = upDir.y; basis(1, 2) = forward.y;
		basis(2, 0) = right.z; basis(2, 1) = upDir.z; basis(2, 2) = forward.z;
		t.rotation = quatFromMat3(basis);
		t.position = from;
		t.scale = vec3One<T>();
		markDirty(&t);
		return t;
	}

	template<typename T>
	quat<T> getForward(const Transform3D<T>& t) {
		return quatRotate(t.rotation, vec3Forward<T>());
	}

	template<typename T>
	Transform3D<T> transformFromPosition(vec<T, 3> position) {
		Transform3D<T> t;
		t.position = position;
		markDirty(&t);
		return t;
	}

	template<typename T>
	Transform3D<T> transformFromRotation(quat<T> rotation) {
		Transform3D<T> t;
		t.rotation = rotation;
		markDirty(&t);
		return t;
	}

	template<typename T>
	Transform3D<T> transformFromPositionRotation(vec<T, 3> position, quat<T> rotation) {
		Transform3D<T> t;
		t.position = position;
		t.rotation = rotation;
		markDirty(&t);
		return t;
	}

	template<typename T>
	Transform3D<T> transformFromPositionRotationScale(vec<T, 3> position, quat<T> rotation, vec<T, 3> scale) {
		Transform3D<T> t;
		t.position = position;
		t.rotation = rotation;
		t.scale = scale;
		markDirty(&t);
		return t;
	}

	template<typename T>
	void translate(Transform3D<T>* transform, vec<T, 3> translation) {
		transform->position += translation;
		markDirty(transform);
	}

	template<typename T>
	void rotate(Transform3D<T>* transform, quat<T> rotation) {
		transform->rotation = quatMultiply(transform->rotation, rotation);
		markDirty(transform);
	}

	template<typename T>
	void scale(Transform3D<T>* transform, vec<T, 3> scale) {
		transform->scale *= scale;
		markDirty(transform);
	}

	template<typename T>
	Transform3D<T> getParent(Transform3D<T>* transform) {
		return transform->parent ? *transform->parent : Transform3D<T>();
	}

	template<typename T>
	void setParent(Transform3D<T>* transform, Transform3D<T>* parent) {
		transform->parent = parent;
		markDirty(transform);
	}

	template<typename T>
	vec<T, 3> getPosition(const Transform3D<T>* transform) {
		return transform->position;
	}

	template<typename T>
	void setPosition(Transform3D<T>* transform, vec<T, 3> position) {
		transform->position = position;
		markDirty(transform);
	}

	template<typename T>
	quat<T> getRotation(const Transform3D<T>* transform) {
		return transform->rotation;
	}

	template<typename T>
	void setRotation(Transform3D<T>* transform, quat<T> rotation) {
		transform->rotation = rotation;
		markDirty(transform);
	}

	template<typename T>
	vec<T, 3> getScale(const Transform3D<T>* transform) {
		return transform->scale;
	}

	template<typename T>
	void setScale(Transform3D<T>* transform, vec<T, 3> scale) {
		transform->scale = scale;
		markDirty(transform);
	}

	template<typename T>
	void markDirty(Transform3D<T>* transform) {
		t

			template<typename T>
		Matrix<T, 4, 4> getLocal(Transform3D<T>*transform) {
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
		Matrix<T, 4, 4> getWorld(Transform3D<T>*transform) {
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
}
#pragma once

#include "Elysium/Core.h"
#include "Matrix.hpp"
#include "Vec4.hpp"

namespace Math {
	typedef vec4 quat;
	
	INLINE quat quatIdentity() {
		return quat(0, 0, 0, 1.0f);
	}

	INLINE float quatNormal(quat q) {
		return fsqrt(
			q.x * q.x +
			q.y * q.y +
			q.z * q.z +
			q.w * q.w
		);
	}

	INLINE quat quatNormalize(quat q) {
		float norm = (quatNormal(q) <= 0) ? quatNormal(q) : 0.0f;
		return quat(q.x / norm, q.y / norm, q.z / norm, q.w / norm);
	}

	INLINE quat quatConjugate(quat q) {
		return quat(-q.x, -q.y, -q.z, q.w);
	}

	INLINE quat quatInverse(quat q) {
		return quatNormalize(quatConjugate(q));
	}

	INLINE quat quatMul(quat q, quat r) {
		quat t;

		t.x = r.w * q.x + r.x * q.w - r.y * q.z + r.z * q.y;
		t.y = r.w * q.y + r.x * q.z + r.y * q.w - r.z * q.x;
		t.z = r.w * q.z - r.x * q.y + r.y * q.x + r.z * q.w;
		t.w = r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z;

		return t;
	}

	INLINE float quatDot(quat q, quat r) {
		return q.x * r.x + q.y * r.y + q.z * r.z + q.w * r.w;
	}

	INLINE mat4 quatToMat4(quat q) {
		mat4 mat = mat4::identity();
		quat n = quatNormalize(q);

		float x = n.x, y = n.y, z = n.z, w = n.w;
		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;


		mat.data[0] = 1.0f - 2.0f * (yy + zz);
		mat.data[1] = 2.0f * (xy - wz);
		mat.data[2] = 2.0f * (xz + wy);

		mat.data[4] = 2.0f * (xy + wz);
		mat.data[5] = 1.0f - 2.0f * (xx + zz);
		mat.data[6] = 2.0f * (yz - wx);

		mat.data[8] = 2.0f * (xz - wy);
		mat.data[9] = 2.0f * (yz + wx);
		mat.data[10] = 1.0f - 2.0f * (xx + yy);

		return mat;
	}

	INLINE mat4 quatToRotMatrix(quat q, vec3 center) {
		q = quatNormalize(q);

		float x = q.x, y = q.y, z = q.z, w = q.w;
		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;

		mat4 mat = mat4::identity();

		mat(0, 0) = 1.0f - 2.0f * (yy + zz);
		mat(0, 1) = 2.0f * (xy - wz);
		mat(0, 2) = 2.0f * (xz + wy);
		mat(0, 3) = 0.0f;

		mat(1, 0) = 2.0f * (xy + wz);
		mat(1, 1) = 1.0f - 2.0f * (xx + zz);
		mat(1, 2) = 2.0f * (yz - wx);
		mat(1, 3) = 0.0f;

		mat(2, 0) = 2.0f * (xz - wy);
		mat(2, 1) = 2.0f * (yz + wx);
		mat(2, 2) = 1.0f - 2.0f * (xx + yy);
		mat(2, 3) = 0.0f;

		// Compute translation so that the rotation is centered around `center`
		float tx = center.x - (mat(0, 0) * center.x + mat(0, 1) * center.y + mat(0, 2) * center.z);
		float ty = center.y - (mat(1, 0) * center.x + mat(1, 1) * center.y + mat(1, 2) * center.z);
		float tz = center.z - (mat(2, 0) * center.x + mat(2, 1) * center.y + mat(2, 2) * center.z);

		mat(3, 0) = tx;
		mat(3, 1) = ty;
		mat(3, 2) = tz;
		mat(3, 3) = 1.0f;

		return mat;
	}

	INLINE quat quatFromAxisAngle(vec3 axis, float angle, char normalize) {
		const float half_angle = 0.5f * angle;

		float s = sin(half_angle);
		float c = cos(half_angle);

		quat q = quat(s * axis.x, s * axis.y, s * axis.z, c);

		if (normalize) {
			return quatNormalize(q);
		}

		return q;
	}

	/**
	*
	*	@param q Starting quaternion value
	*	@param r Ending quaternion value
	*	@param t Interpolation ratio. Value range is [0, 1].
	*/
	INLINE quat quatSlerp(quat q, quat r, float t) {
		q = quatNormalize(q);
		r = quatNormalize(r);
		quat result;
		float cosHalfTheta = quatDot(q, r);

		if (cosHalfTheta < 0.0f) {
			r.x = -r.x;
			r.y = -r.y;
			r.z = -r.z;
			r.w = -r.w;
			cosHalfTheta = -cosHalfTheta;
		}

		const float DOT_THRESHOLD = 0.9995f;
		if (cosHalfTheta > DOT_THRESHOLD) {
			// Linear interpolation + normalize
			for (int i = 0; i < 4; ++i)
				result.elements[i] = q.elements[i] + (r.elements[i] - q.elements[i]) * t;
			return quatNormalize(result);
		}


		float theta = acosf(cosHalfTheta);
		float sinTheta = sinf(theta);

		float s0 = sinf((1 - t) * theta) / sinTheta;
		float s1 = sinf(t * theta) / sinTheta;

		for (int i = 0; i < 4; ++i)
			result.elements[i] = q.elements[i] * s0 + r.elements[i] * s1;

		return quatNormalize(result);
	}
}
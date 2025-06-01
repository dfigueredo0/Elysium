#pragma once

#include "Elysium/Math/Math.hpp"

namespace Elysium {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const vec3& GetPosition() const { return m_Position; }
		void SetPosition(const vec3& position) { 
			m_Position = position; 
			RecalculateViewMatrix();
		}

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { 
			m_Rotation = rotation; 
			RecalculateViewMatrix(); 
		}

		const mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const mat4& getViewMatrix() const { return m_ViewMatrix; }
		const mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

		mat4 m_ProjectionMatrix;
		mat4 m_ViewMatrix;
		mat4 m_ViewProjectionMatrix;

		vec3 m_Position;
		float m_Rotation = 0.0f;
	};

	class PerspectiveCamera {
	public:
	private:
		mat4 m_ProjectionMatrix;
		mat4 m_ViewMatrix;
		mat4 m_ScaleMatrix;
		mat4 m_ViewProjectionMatrix;

		vec3 m_Position;
		Math::quatf m_Rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	};
}
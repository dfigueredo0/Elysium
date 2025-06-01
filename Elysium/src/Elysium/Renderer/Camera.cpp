#include "elypch.h"

#include "Camera.h"

namespace Elysium {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(Math::orthographic(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		//Some type of clamping being done makes rotation weird when angle goes high enough
		mat4 rotation = Math::rotateMatrix(Math::degToRad(m_Rotation), vec3(0, 0, 1));
		mat4 translation = Math::translateMatrix(m_Position);

		m_ViewMatrix = rotation * translation;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
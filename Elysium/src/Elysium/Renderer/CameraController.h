#pragma once


#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Events/MouseEvent.h"
#include "Elysium/Core/Timestep.h"
#include "Elysium/Renderer/Camera.h"

namespace Elysium {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 1.0f; //Make into a function based on zoom level
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 30.0f;
	};
}
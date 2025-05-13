#pragma once

#include "Elysium/Layers/Layer.h"

#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Events/MouseEvent.h"
#include "Elysium/Events/KeyEvent.h"

/* TODO: Maybe create my own UI Library */
namespace Elysium {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		void OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		void OnMouseMovedEvent(MouseMovedEvent& e);
		void OnMouseScrolledEvent(MouseScrolledEvent& e);
		void OnKeyPressedEvent(KeyPressedEvent& e);
		void OnKeyReleasedEvent(KeyReleasedEvent& e);
		//void OnKeyTypedEvent(KeyTypedEvent& e);
		void OnWindowResizedEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}
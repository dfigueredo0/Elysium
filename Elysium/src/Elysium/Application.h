#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Layers/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Elysium/Core/Timestep.h"

#include "Elysium/ImGui/ImGuiLayer.h"

namespace Elysium {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// Defined in CLIENT
	Application* CreateApplication();
}

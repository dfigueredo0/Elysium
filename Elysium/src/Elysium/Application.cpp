#include "elypch.h"
#include "Application.h"

#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Log.h"

namespace Elysium
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			ELY_CORE_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			ELY_CORE_TRACE(e.ToString());
		}

		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
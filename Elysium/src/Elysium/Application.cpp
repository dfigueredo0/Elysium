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
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
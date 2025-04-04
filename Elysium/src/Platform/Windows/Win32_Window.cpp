#include "elypch.h"
#include "Win32_Window.h"

namespace Elysium {
	Window* Window::Create(const WindowProps& props) {
		return new Win32_Window(props);
	}

	Win32_Window::Win32_Window(const WindowProps& props)
	{
		Init(props);
	}

	Win32_Window::~Win32_Window()
	{
		Shutdown();
	}

	void Win32_Window::OnUpdate()
	{
	}

	void Win32_Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool Win32_Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	void Win32_Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ELY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		SetVSync(true);
	}

	void Win32_Window::Shutdown()
	{
	}
}

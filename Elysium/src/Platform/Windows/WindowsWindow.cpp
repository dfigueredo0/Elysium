#include "elypch.h"
#include "WindowsWindow.h"

namespace Elysium {
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	Elysium::WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void Elysium::WindowsWindow::OnUpdate() {
	}

	void Elysium::WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			; // TODO: OpenGL swap interval (1)
		else
			;// TODO: OpenGL swap interval (0)

		m_Data.VSync = enabled;
	}

	bool Elysium::WindowsWindow::IsVsync() const {
		return false;
	}

	void Elysium::WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		ELY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		SetVSync(true)
	}

	void Elysium::WindowsWindow::Shutdown() {
	}
}
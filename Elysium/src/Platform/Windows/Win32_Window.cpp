#include "elypch.h"

#include "Elysium/KeyCodeTranslation.hpp"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Win32_Window.h"

#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Events/MouseEvent.h"
#include "Elysium/Events/KeyEvent.h"

#include "Elysium/Renderer/RenderContext.h"

namespace Elysium {
	static bool s_GLFWInitialized = false;

	static void ErrorCallback(int err, const char* desc) {
		ELY_CORE_ERROR("GLFW Error ({0}): {1}", err, desc);
	}

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
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Win32_Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

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

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown 
			int success = glfwInit();
			ELY_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(ErrorCallback);
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		RegisterCallbacks();
	}

	void Win32_Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Win32_Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	}

	void Win32_Window::WindowCloseCallback(GLFWwindow* window)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	}

	void Win32_Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(TranslateFromGLFWKey(key), 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(TranslateFromGLFWKey(key));
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(TranslateFromGLFWKey(key), 1);
			data.EventCallback(event);
			break;
		}
		}
	}

	void Win32_Window::KeyCharCallback(GLFWwindow* window, unsigned int keycode) {
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	}

	void Win32_Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
	}

	void Win32_Window::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	}

	void Win32_Window::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{
		auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	}

	void Win32_Window::RegisterCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetCharCallback(m_Window, KeyCharCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetScrollCallback(m_Window, ScrollCallback);
		glfwSetCursorPosCallback(m_Window, CursorPosCallback);
	}

}

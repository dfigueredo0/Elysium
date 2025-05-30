#pragma once

#include "Elysium/Window.h"

#include <GLFW/glfw3.h>

namespace Elysium {
	class Win32_Window : public Window {
	public:
		Win32_Window(const WindowProps& props);
		virtual ~Win32_Window();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		static void WindowResizeCallback(GLFWwindow*, int, int);
		static void WindowCloseCallback(GLFWwindow*);
		static void KeyCallback(GLFWwindow*, int, int, int, int);
		static void KeyCharCallback(GLFWwindow*, unsigned int);
		static void MouseButtonCallback(GLFWwindow*, int, int, int);
		static void ScrollCallback(GLFWwindow*, double, double);
		static void CursorPosCallback(GLFWwindow*, double, double);

		void RegisterCallbacks();
	private:
		GLFWwindow* m_Window;
		RenderContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width = 1280, Height = 720;
			bool VSync = true;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
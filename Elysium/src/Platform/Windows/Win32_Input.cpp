#include "elypch.h"
#include "Win32_Input.h"
#include "Elysium/Application.h"

#include <GLFW/glfw3.h>

namespace Elysium {

	Input* Input::s_Instance = new Win32_Input();

	bool Win32_Input::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Win32_Input::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Win32_Input::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Win32_Input::GetMouseXImpl() {
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float Win32_Input::GetMouseYImpl() {
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}
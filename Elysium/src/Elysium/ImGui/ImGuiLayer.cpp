#include "elypch.h"

#include "ImGuiLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Elysium/Application.h"

//TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Elysium {
	//TEMP: should eventually use Elysium key codes
	static const std::unordered_map<int, ImGuiKey> s_GLFWToImGuiKeyMap = {
		{ GLFW_KEY_TAB, ImGuiKey_Tab },
		{ GLFW_KEY_LEFT, ImGuiKey_LeftArrow },
		{ GLFW_KEY_RIGHT, ImGuiKey_RightArrow },
		{ GLFW_KEY_UP, ImGuiKey_UpArrow },
		{ GLFW_KEY_DOWN, ImGuiKey_DownArrow },
		{ GLFW_KEY_PAGE_UP, ImGuiKey_PageUp },
		{ GLFW_KEY_PAGE_DOWN, ImGuiKey_PageDown },
		{ GLFW_KEY_HOME, ImGuiKey_Home },
		{ GLFW_KEY_END, ImGuiKey_End },
		{ GLFW_KEY_INSERT, ImGuiKey_Insert },
		{ GLFW_KEY_DELETE, ImGuiKey_Delete },
		{ GLFW_KEY_BACKSPACE, ImGuiKey_Backspace },
		{ GLFW_KEY_SPACE, ImGuiKey_Space },
		{ GLFW_KEY_ENTER, ImGuiKey_Enter },
		{ GLFW_KEY_ESCAPE, ImGuiKey_Escape },
		{ GLFW_KEY_A, ImGuiKey_A },
		{ GLFW_KEY_B, ImGuiKey_B },
		{ GLFW_KEY_C, ImGuiKey_C },
		{ GLFW_KEY_D, ImGuiKey_D },
		{ GLFW_KEY_E, ImGuiKey_E },
		{ GLFW_KEY_F, ImGuiKey_F },
		{ GLFW_KEY_G, ImGuiKey_G },
		{ GLFW_KEY_H, ImGuiKey_H },
		{ GLFW_KEY_I, ImGuiKey_I },
		{ GLFW_KEY_J, ImGuiKey_J },
		{ GLFW_KEY_K, ImGuiKey_K },
		{ GLFW_KEY_L, ImGuiKey_L },
		{ GLFW_KEY_M, ImGuiKey_M },
		{ GLFW_KEY_N, ImGuiKey_N },
		{ GLFW_KEY_O, ImGuiKey_O },
		{ GLFW_KEY_P, ImGuiKey_P },
		{ GLFW_KEY_Q, ImGuiKey_Q },
		{ GLFW_KEY_R, ImGuiKey_R },
		{ GLFW_KEY_S, ImGuiKey_S },
		{ GLFW_KEY_T, ImGuiKey_T },
		{ GLFW_KEY_U, ImGuiKey_U },
		{ GLFW_KEY_V, ImGuiKey_V },
		{ GLFW_KEY_W, ImGuiKey_W },
		{ GLFW_KEY_X, ImGuiKey_X },
		{ GLFW_KEY_Y, ImGuiKey_Y },
		{ GLFW_KEY_Z, ImGuiKey_Z },
	};

	static ImGuiKey ConvertGLFWtoImGuiKey(int keycode) {
		auto it = s_GLFWToImGuiKeyMap.find(keycode);
		return (it != s_GLFWToImGuiKeyMap.end()) ? it->second : ImGuiKey_None;
	}

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}
	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ELY_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), true);
		return false; // Don't want this layer to soak up every mouse event, later can check if a button was actually clicked
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false);
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey keycode = ConvertGLFWtoImGuiKey(e.GetKeyCode());
		io.AddKeyEvent(keycode, true);
		return false;
		
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey keycode = ConvertGLFWtoImGuiKey(e.GetKeyCode());
		io.AddKeyEvent(keycode, false);
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}
		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight()); //for now

		return false;
	}
}
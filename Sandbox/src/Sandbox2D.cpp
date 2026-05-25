#include "Sandbox2D.h"
#include "imgui.h"

#include <Elysium/Math/Math.hpp>
#include <Elysium/Math/type_ptr.hpp>

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 1720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Elysium::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Elysium::Timestep ts)
{
	ELY_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Elysium::RenderCommand::Clear({ 0.13f, 0.13f, 0.13f, 1.0f });

	Elysium::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Elysium::Renderer2D::DrawQuad(vec2(-1.0f, 0.0f), { 0.8f, 0.8f }, { 0.8f, 0.3f, 0.2f, 1.0f });
	Elysium::Renderer2D::DrawQuad(vec2(0.5f, -0.5f), { 1.0f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Elysium::Renderer2D::DrawQuad(vec3(0.0f, 0.0f, 0.0f), { 10.0f, 10.0f }, m_Texture);
	Elysium::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", Math::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Elysium::Event& e)
{
	m_CameraController.OnEvent(e);
}

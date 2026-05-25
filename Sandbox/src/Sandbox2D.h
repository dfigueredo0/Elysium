#pragma once

#include <Elysium.h>

class Sandbox2D : public Elysium::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Elysium::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Elysium::Event& e) override;
private:
	Elysium::OrthographicCameraController m_CameraController;

	Elysium::Ref<Elysium::VertexArray> m_SquareVA;
	Elysium::Ref<Elysium::Shader> m_FlatColorShader;

	Elysium::Ref<Elysium::Texture2D> m_Texture;

	vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
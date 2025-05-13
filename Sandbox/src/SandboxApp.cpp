#include <Elysium.h>

class ExampleLayer : public Elysium::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {
		ELY_INFO("ExampleLayer::Update");
	}

	void OnEvent(Elysium::Event& e) override {
		ELY_TRACE("{0}", e.ToString());
	}
};

class Sandbox : public Elysium::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Elysium::ImGuiLayer());
	}
	~Sandbox() {
	}
};

Elysium::Application* Elysium::CreateApplication() {
	return new Sandbox();
}
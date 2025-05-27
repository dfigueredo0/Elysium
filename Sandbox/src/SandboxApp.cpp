#include <Elysium.h>

class ExampleLayer : public Elysium::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {

	}

	void OnEvent(Elysium::Event& e) override {
	
	}
};

class Sandbox : public Elysium::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

Elysium::Application* Elysium::CreateApplication() {
	return new Sandbox();
}
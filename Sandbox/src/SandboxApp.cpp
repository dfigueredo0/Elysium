#include "Elysium.h"

class Sandbox : public Elysium::Application {
public:
	Sandbox() {
	}
	~Sandbox() {
	}
};

Elysium::Application* Elysium::CreateApplication() {
	return new Sandbox();
}
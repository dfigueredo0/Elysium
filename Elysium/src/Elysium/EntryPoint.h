#pragma once

#ifdef ELY_PLATFORM_WINDOWS

extern Elysium::Application* Elysium::CreateApplication();

int main(int argc, char** argv) {
	Elysium::Log::Init();
	ELY_CORE_WARN("Initialized Log!");

	auto app = Elysium::CreateApplication();
	app->Run();
	delete app;
}
#endif // ELY_PLATFORM_WINDOWS
#pragma once

#ifdef ELY_PLATFORM_WINDOWS

extern Elysium::Application* Elysium::CreateApplication();

int main(int argc, char** argv) {
	Elysium::Log::Init();

	ELY_PROFILE_BEGIN_SESSION("Startup", "ElysiumProfile-Startup.json");
	auto app = Elysium::CreateApplication();
	ELY_PROFILE_END_SESSION();

	ELY_PROFILE_BEGIN_SESSION("Runtime", "ElysiumProfile-Runtime.json");
	app->Run();
	ELY_PROFILE_END_SESSION();

	ELY_PROFILE_BEGIN_SESSION("Shutdown", "ElysiumProfile-Shutdown.json");
	delete app;
	ELY_PROFILE_END_SESSION();
}
#endif // ELY_PLATFORM_WINDOWS
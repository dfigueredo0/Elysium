#pragma once

#ifdef ELY_PLATFORM_WINDOWS

extern Elysium::Application* Elysium::CreateApplication();

int main(int argc, char** argv) {
	//Elysium::Log::Init();
	//ELY_CORE_WARN("Initialized Log!");
	//int a = 5;
	//ELY_INFO("Hello! Var={0}", a);
	auto app = Elysium::CreateApplication();
	app->Run();
	delete app;
}
#endif // ELY_PLATFORM_WINDOWS


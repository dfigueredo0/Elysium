#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Elysium {
	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#pragma region Core Log Macros
#define ELY_CORE_TRACE(...)::Elysium::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ELY_CORE_INFO(...)::Elysium::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ELY_CORE_WARN(...)::Elysium::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ELY_CORE_ERROR(...)::Elysium::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ELY_CORE_FATAL(...)::Elysium::Log::GetCoreLogger()->critical(__VA_ARGS__)
#pragma endregion

#pragma region Client Log Macros
#define ELY_TRACE(...)::Elysium::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ELY_INFO(...)::Elysium::Log::GetClientLogger()->info(__VA_ARGS__)
#define ELY_WARN(...)::Elysium::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ELY_ERROR(...)::Elysium::Log::GetClientLogger()->error(__VA_ARGS__)
#define ELY_FATAL(...)::Elysium::Log::GetClientLogger()->critical(__VA_ARGS__)
#pragma endregion
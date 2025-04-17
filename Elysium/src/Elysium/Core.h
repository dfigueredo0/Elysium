#pragma once

#ifdef ELY_PLATFORM_WINDOWS
#ifdef ELY_BUILD_DLL
#define ELYSIUM_API __declspec(dllexport)
#else
#define ELYSIUM_API __declspec(dllimport)
#endif
#else
#error Elysium only supports Windows!
#endif

#ifdef ELY_ENABLE_ASSERTS
#define ELY_ASSERT(x, ...) { if (!x) {ELY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ELY_CORE_ASSERT(x, ...) { if (!x) {ELY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ELY_ASSERT(x, ...) 
#define ELY_CORE_ASSERT(x, ...)
#endif // ELY_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define ELY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
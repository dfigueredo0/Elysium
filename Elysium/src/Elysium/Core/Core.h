#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define ELY_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS sim is not currently supported!"
	#elif TARGET_OS_IPHONE
		#define ELY_PLATFORM_IOS
		#error "IOS is not currently supported!"
	#elif TARGET_OS_MAC == 1
		#define ELY_PLATFORM_MAC
		#error "MacOS is not currently supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define ELY_PLATFORM_ANDRIOD
	#error "Andriod is not currently supported!"
#elif defined(__linux__)
	#define ELY_PLATFORM_LINUX
	#error "Linux is not currently supported!"
#else
	#error "Unknown platform!"
#endif // Platform Detection

#ifdef ELY_ENABLE_ASSERTS
#define ELY_ASSERT(x, ...) { if (!x) {ELY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ELY_CORE_ASSERT(x, ...) { if (!x) {ELY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ELY_ASSERT(x, ...) 
#define ELY_CORE_ASSERT(x, ...)
#endif // ELY_ENABLE_ASSERTS

#define BIT(x) (1 << x)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

#define ELY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef _MSC_VER
#define INLINE __forceinline
#define NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define INLINE inline __attribute__((always_inline))
#define NOINLINE
#else
#define INLINE static inline
#define NOINLINE
#endif

namespace Elysium {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
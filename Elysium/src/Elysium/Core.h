#pragma once

#ifdef _WIN32
	#ifdef ELY_BUILD_DLL
		#define ELYSIUM_API __declspec(dllexport)
	#else
		#define ELYSIUM_API __declspec(dllimport)
	#endif
	#else
		#define ELYSIUM_API __attribute__((visibility("default")))
#endif

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
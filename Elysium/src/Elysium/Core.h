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
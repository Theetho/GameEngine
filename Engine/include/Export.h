#pragma once

#ifdef ENGINE_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // ENGINE_BUILD_DLL
#endif // ENGINE_WINDOWS

#ifdef ENGINE_DEBUG
	#define ENGINE_ENABLE_ASSERTS
#endif // ENGINE_DEBUG


#ifdef ENGINE_ENABLE_ASSERTS
	#define APP_ASSERT(x, ...) { if(!(x)) { APP_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define APP_ASSERT(x, ...)
	#define ENGINE_ASSERT(x, ...)
#endif
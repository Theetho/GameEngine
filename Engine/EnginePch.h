#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <functional>
#include <initializer_list>

#ifdef ENGINE_WINDOWS
	#include "glad/glad.h"
	#include "GLFW/glfw3.h"
#endif // ENGINE_WINDOWS

#include "Core/InputCodes.h"

#ifdef ENGINE_ENABLE_ASSERTS
#define APP_ASSERT(x, ...) { if(!(x)) { APP_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define APP_ASSERT(x, ...)
#define ENGINE_ASSERT(x, ...)
#endif

namespace Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
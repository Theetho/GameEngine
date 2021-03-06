#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <array>
#include <functional>
#include <initializer_list>
#include <algorithm>
#include <typeindex>
#include <typeinfo>
#include <stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype-gl.h>
#include "imgui.h"

#ifdef ENGINE_WINDOWS
	#include "glad/glad.h"
	#include "GLFW/glfw3.h"
	#include "imgui_impl_glfw.h"
	#include "imgui_impl_opengl3.h"
#endif // ENGINE_WINDOWS

#ifdef ENGINE_ENABLE_ASSERTS
	#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define APP_ASSERT(x, ...) { if(!(x)) { APP_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ENGINE_ASSERT(x, ...)
	#define APP_ASSERT(x, ...)
#endif

namespace Engine
{
	// From the cherno's code
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Weak = std::weak_ptr<T>;

	template<typename T>
	void Debug(std::initializer_list<T> args)
	{
		for (auto& arg : args)
		{
			std::cout << arg << " ";
		}
		std::cout << std::endl;
	}

	using uint = unsigned int;
}

#include "Include/Maths.h"
#include "Core/Log.h"
#include "Core/InputCodes.h"
#include "Include/Util.h"
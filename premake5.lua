workspace "GameEngine"
	architecture "x64"
	configurations {"Debug", "Release", "Distribution"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-x64"

include "Engine/vendor/GLFW"
include "Engine/vendor/glad"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "%{prj.name}Pch.h"
	pchsource "%{prj.name}/src/%{prj.name}Pch.cpp"

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	libdirs
	{
		"lib/windows/x64"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	defines
	{
		"ENGINE_WINDOWS",
		"ENGINE_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
	}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"
	filter "configurations:Distribution"
		defines "ENGINE_DISTRIBUTION"
		optimize "On"	

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	architecture "x64"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"
	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/vendor/GLFW/include",
		"Engine/vendor/glad/include",
		"Engine/include",
		"%{prj.name}/include"
	}
	
	links
	{
		"Engine",
		"opengl32.lib"
	}
	
	libdirs
	{
		"lib/windows/x64"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
	defines
	{
		"ENGINE_WINDOWS"
	}
	
	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"
	filter "configurations:Distribution"
		defines "ENGINE_DISTRIBUTION"
		optimize "On"

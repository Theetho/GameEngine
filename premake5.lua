workspace "GameEngine"
	architecture "x64"
	configurations {"Debug", "Release", "Distribution"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-x64"

include "Engine/Vendor/GLFW"
include "Engine/Vendor/glad"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "%{prj.name}Pch.h"
	pchsource "%{prj.name}/%{prj.name}Pch.cpp"

	files
	{
		"%{prj.name}/*/*.h",
		"%{prj.name}/*.h",
		"%{prj.name}/*/*.cpp",
		"%{prj.name}/*.cpp",
		"%{prj.name}/Component/Collider/*",
		"%{prj.name}/API/OpenGL/*",
		"%{prj.name}/Renderer/Buffer/*",
		"%{prj.name}/Renderer/Rendering/*",
		"%{prj.name}/Renderer/Texture/*",
		"%{prj.name}/Vendor/stb/*",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/Vendor/*/include",
		"%{prj.name}/Vendor/glm",
		"%{prj.name}/Vendor/stb",
		"%{prj.name}/Vendor/assimp-5.0.0/include",
		"%{prj.name}"
	}

	filter "system:windows"
		systemversion "latest"

		libdirs
		{
			"lib/windows/x64"
		}

		links
		{
			"GLFW",
			"GLAD",
			"opengl32.lib",
			"assimp-vc142-mt.lib"
		}

		defines
		{
			"ENGINE_FILES",
			"ENGINE_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Distribution"
		defines "ENGINE_DISTRIBUTION"
		runtime "Release"
		optimize "on"	

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/pch.cpp"
	
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Engine/Vendor/*/include",
		"Engine/..",
		"Engine/Vendor/glm",
		"Engine/Vendor/stb",
		"%{prj.name}"
	}
	
	links
	{
		"Engine",
		"opengl32.lib",
		"assimp-vc142-mt.lib",
	}	
	
	libdirs
	{
		"lib/windows/x64"
	}
	
	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"ENGINE_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Distribution"
		defines "ENGINE_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "2DDevelop"
	location "2DDevelop"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"%{prj.name}",
		"%{prj.name}/SFML/include"
	}
	
	links
	{
		"sfml-main.lib",
		"sfml-audio.lib",
		"sfml-window.lib",
		"sfml-graphics.lib",
		"sfml-network.lib",
		"sfml-system.lib"
	}	
	
	libdirs
	{
		"%{prj.name}/SFML/lib/x64"
	}
	
	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"ENGINE_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Distribution"
		defines "ENGINE_DISTRIBUTION"
		runtime "Release"
		optimize "On"

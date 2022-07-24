include "thirdparty"

project "Jerboa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jerboa-pch.h"
	pchsource "src/jerboa-pch.cpp"
	
	defines {
		"JERBOA_CORE"
	}

	files 
	{ 
		"src/**.h", 
		"src/**.c", 
		"src/**.hpp", 
		"src/**.cpp" 
	}

	includedirs
	{
		jerboa_includedirs
	}
    
	links 
	{ 
		"spdlog",
		"glfw",
		"glad",
		"ImGui",
		"assimp",
		"OptickCore"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines 
		{ 
			"JERBOA_PLATFORM_WINDOWS",
			"JERBOA_RENDER_API_OPENGL"
		}

	filter "configurations:Debug"
		defines "JERBOA_DEBUG"
		defines { "JERBOA_DEBUG", "USE_OPTICK=1" }
		symbols "On"

	filter "configurations:Staging"
		defines { "JERBOA_STAGING", "USE_OPTICK=1" }
		optimize "On"

	filter "configurations:Release"
		defines { "JERBOA_RELEASE", "USE_OPTICK=0" }
		defines "JERBOA_RELEASE"
		optimize "On"
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

	--includedirs
	--{
	--	"src", 
	--	"thirdparty/spdlog/include"
	--}
    
	links 
	{ 
		"spdlog",
		"glfw"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines 
		{ 
			"JERBOA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JERBOA_DEBUG"
		symbols "On"
				
	filter "configurations:Staging"
		defines "JERBOA_STAGING"
		optimize "On"

	filter "configurations:Release"
		defines "JERBOA_RELEASE"
		optimize "On"
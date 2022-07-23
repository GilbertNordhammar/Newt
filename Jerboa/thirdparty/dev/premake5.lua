workspace "jeroba-thirdparty"
    architecture "x64"
    targetdir "build"

    configurations 
	{ 
		"Debug"
	}

    startproject "Sandbox"

include "../"
    
project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
	    "src/**.h", 
		"src/**.c", 
		"src/**.hpp", 
		"src/**.cpp" 
	}

	includedirs
	{
        "src",
        "thirdparty",
		"../spdlog/include",
		"../glfw/include"
	}

	links
	{
		"spdlog",
		"glfw"
	}

	filter "system:windows"
	  	systemversion "latest"

	filter "configurations:Debug"
	   	symbols "On"
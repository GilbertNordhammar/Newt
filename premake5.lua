workspace "Jerboa"
    architecture "x64"
    targetdir "build"

    configurations 
	{ 
		"Debug", 
		"Staging",
		"Release"
	}

	startproject "JerboaClient"
	  
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

jerboa_includedirs =  { 
	"%{wks.location}/Jerboa/src", 
	"%{wks.location}/Jerboa/thirdparty/spdlog/include", 
	"%{wks.location}/Jerboa/thirdparty/glfw/include", 
	"%{wks.location}/Jerboa/thirdparty/glad/include",
	"%{wks.location}/Jerboa/thirdparty/imgui",
	"%{wks.location}/Jerboa/thirdparty/imgui/backends",
	"%{wks.location}/Jerboa/thirdparty/assimp/include",
	"%{wks.location}/Jerboa/thirdparty/assimp/build/include",
	"%{wks.location}/Jerboa/thirdparty/glm",
	"%{wks.location}/Jerboa/thirdparty/stb",
	"%{wks.location}/Jerboa/thirdparty/optick/src",
}

include "Jerboa"
include "Sandbox"
include "JerboaClient"
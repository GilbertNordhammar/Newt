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
	"src", 
	"thirdparty/spdlog/include", 
	"thirdparty/glfw/include", 
	"thirdparty/glad/include",
	"thirdparty/imgui",
	"thirdparty/imgui/examples"
}

jerboa_app_includedirs = {}
for _, v in pairs(jerboa_includedirs) do
	table.insert(jerboa_app_includedirs, "%{wks.location}/Jerboa/" .. v)
end

include "Jerboa"
include "Sandbox"
include "JerboaClient"



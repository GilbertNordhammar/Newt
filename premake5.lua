workspace "Jerboa"
    architecture "x64"
    targetdir "build"

    configurations 
	{ 
		"Debug", 
		"Staging",
		"Release"
	}

	startproject "Sandbox"
	  
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

jerboa_includedirs =  { "src", "thirdparty/spdlog/include" }

jerboa_app_includedirs = {}
for _, v in pairs(jerboa_includedirs) do
	table.insert(jerboa_app_includedirs, "%{wks.location}/Jerboa/" .. v)
end

include "Jerboa"
include "Sandbox"


group "thirdparty"
externalproject "assimp"
    location "assimp/build/code"
    kind "StaticLib"
    language "C++"

    filter "system:windows"
        filename "assimp"

externalproject "spdlog"
    location "spdlog/build"
    kind "StaticLib"
    language "C++"

    filter "system:windows"
        filename "spdlog"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "glfw"
include "glad"
include "imgui"
include "optick"
group ""

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

include "Jerboa"
-- include "Jerboa-editor"  -- TBA
include "Sandbox"


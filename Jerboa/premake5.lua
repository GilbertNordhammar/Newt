project "Jerboa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jerboa-pch.h"
	pchsource "src/jerboa-pch.cpp"

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
		-- "%{IncludeDir.GLFW}",    -- TBA
		-- "%{IncludeDir.Glad}",
		-- "%{IncludeDir.glm}",
		-- "%{IncludeDir.ImGui}",
		-- "%{prj.name}/vendor/assimp/include",
		-- "%{prj.name}/vendor/stb/include"
	}
    
    
	-- links 
	-- { 
	-- 	"GLFW",
	-- 	"Glad",     -- TBA
	-- 	"ImGui",
	-- 	"opengl32.lib"
	-- }
	
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
project "JerboaClient"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
		"Jerboa"
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

		postbuildcommands 
		{
	   		'{COPY} "%{wks.location}/Jerboa/thirdparty/assimp/build/code/Debug/assimp-vc142-mtd.dll" "%{cfg.targetdir}"',
		}
				
	filter "configurations:Staging"
		defines "JERBOA_STAGING"
		optimize "On"

		postbuildcommands 
		{
	   		'{COPY} "%{wks.location}/Jerboa/thirdparty/assimp/build/code/RelWithDebInfo/assimp-vc142-mt.dll" "%{cfg.targetdir}"',
		}

	filter "configurations:Release"
		defines "JERBOA_RELEASE"
		optimize "On"

		postbuildcommands 
		{
	   		'{COPY} "%{wks.location}/Jerboa/thirdparty/assimp/build/code/Release/assimp-vc142-mt.dll" "%{cfg.targetdir}"',
		}
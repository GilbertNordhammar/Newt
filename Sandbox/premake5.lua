project "Sandbox"
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
        "%{wks.location}/Jerboa/src",
        "%{wks.location}/Jerboa/thirdparty"
		-- "%{wks.location}/Hazel/vendor/spdlog/include",   -- TBA
		-- "%{wks.location}/Hazel/src",
		-- "%{wks.location}/Hazel/vendor",
		-- "%{IncludeDir.glm}",
		-- "%{IncludeDir.entt}"
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
				
	filter "configurations:Staging"
		defines "JERBOA_STAGING"
		optimize "On"

	filter "configurations:Release"
		defines "JERBOA_RELEASE"
		optimize "On"
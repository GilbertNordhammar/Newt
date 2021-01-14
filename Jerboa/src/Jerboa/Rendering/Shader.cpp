#include "jerboa-pch.h"
#include "Shader.h"

#include "Jerboa/Platform/OpenGL/OpenGL_Shader.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::shared_ptr<Shader> shader;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL: 
				shader = std::make_shared<OpenGL_Shader>(vertexPath, fragmentPath);
		}

		JERBOA_ASSERT(shader, "Implementation is missing or render API is not set");
		return shader;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& path)
	{
		std::shared_ptr<Shader> shader;

		switch (Platform::GetRenderApi()) {
		case RenderAPI::OpenGL:
			shader = std::make_shared<OpenGL_Shader>(path);
		}

		JERBOA_ASSERT(shader, "Implementation is missing or render API is not set");
		return shader;
	}
}
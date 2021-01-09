#include "jerboa-pch.h"
#include "Shader.h"

#include "Jerboa/Platform/OpenGL/OpenGL_Shader.h"

namespace Jerboa {
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		return std::make_shared<OpenGL_Shader>(vertexPath, fragmentPath);
	}
}
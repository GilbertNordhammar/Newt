#pragma once

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include <string>
#include <string_view>

namespace Jerboa::ShaderUtils
{
	GLuint CompileShader(std::string_view name, const std::string& shaderCode, GLenum shaderType);
	GLuint CreateAndLinkProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
	bool ShaderCompiledSuccessfully(GLuint shader, std::string_view name);
	bool ProgramLinkedSuccessfully(GLuint program);
}

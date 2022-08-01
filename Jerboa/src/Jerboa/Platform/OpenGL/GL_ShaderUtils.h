#pragma once

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include <string>

namespace Jerboa::ShaderUtils
{
	GLuint CompileShader(const std::string& shaderCode, GLenum shaderType);
	GLuint CreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
	void DeleteShaders(GLuint vertexShaderId, GLuint fragmentShaderId);
	void CheckCompileErrors(GLuint shader, const std::string& shaderType);
	void CheckLinkErrors(GLuint program);
}

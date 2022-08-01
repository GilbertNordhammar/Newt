#include "jerboa-pch.h"
#include "GL_ShaderUtils.h"

#include "Jerboa/Debug.h"

namespace Jerboa::ShaderUtils
{
	GLuint CompileShader(const std::string& shaderCode, GLenum shaderType)
	{
		const char* gShaderCode = shaderCode.c_str();
		auto shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &gShaderCode, NULL);
		glCompileShader(shaderID);

		return shaderID;
	}

	GLuint CreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderId);
		glAttachShader(programID, fragmentShaderId);

		glLinkProgram(programID);

		return programID;
	}

	void DeleteShaders(GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	void CheckCompileErrors(GLuint shader, const std::string& shaderType)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			JERBOA_LOG_ERROR("Failed to compile {0} shader!\n{1}", shaderType, infoLog);
		}
	}

	void CheckLinkErrors(GLuint program)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 1024, NULL, infoLog);
			JERBOA_LOG_ERROR("ERROR::PROGRAM_LINKING_ERROR\n {0}", infoLog);
		}
	}
}
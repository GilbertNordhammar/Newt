#include "jerboa-pch.h"
#include "GL_ShaderUtils.h"

#include "Jerboa/Debug.h"

namespace Jerboa::ShaderUtils
{
	GLuint CompileShader(std::string_view name, const std::string& shaderCode, GLenum shaderType)
	{
		const char* gShaderCode = shaderCode.c_str();
		auto shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &gShaderCode, NULL);
		glCompileShader(shaderID);

		if (!ShaderCompiledSuccessfully(shaderID, name))
		{
			shaderID = 0;
			glDeleteShader(shaderID);
		}

		return shaderID;
	}

	GLuint CreateAndLinkProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderId);
		glAttachShader(programID, fragmentShaderId);

		glLinkProgram(programID);
		if (!ProgramLinkedSuccessfully(programID))
		{
			glDeleteProgram(programID);
			programID = 0;
		}

		return programID;
	}

	bool ShaderCompiledSuccessfully(GLuint shader, std::string_view name)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			JERBOA_LOG_ERROR("Failed to compile shader '{0}'\n{1}", name, infoLog);
		}
		return success;
	}

	bool ProgramLinkedSuccessfully(GLuint program)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 1024, NULL, infoLog);
			JERBOA_LOG_ERROR("ERROR::PROGRAM_LINKING_ERROR\n {0}", infoLog);
		}
		return success;
	}
}
#include "jerboa-pch.h"
#include "OpenGL_ShaderLoader.h"

#include "Jerboa/Debug.h"

namespace Jerboa {
	//static const std::string SHADER_LIB_PATH = fileUtils::getFullResourcesPath("shaders/lib/");
	static const std::string SHADER_LIB_PATH = "assets/shaders/lib/";

	GLuint OpenGL_ShaderLoader::Load(
		const std::string& vertexPath,
		const std::string& fragmentPath,
		const std::string& geometryPath)
	{
		std::string vertexCode;
		vertexCode = RetrieveCode(vertexPath);

		std::string fragmentCode;
		fragmentCode = RetrieveCode(fragmentPath);

		std::string geometryCode;
		if (!geometryPath.empty())
		{
			geometryCode = RetrieveCode(geometryPath);
		}

		unsigned int vertexId = CreateAndCompileShader(vertexCode, GL_VERTEX_SHADER);
		unsigned int fragmentId = CreateAndCompileShader(fragmentCode, GL_FRAGMENT_SHADER);
		unsigned int geometryId = 0;
		if (!geometryPath.empty()) {
			geometryId = CreateAndCompileShader(geometryCode, GL_GEOMETRY_SHADER);
		}


//#if !defined(_RELEASE)
		CheckCompileErrors(vertexId, GL_VERTEX_SHADER, vertexPath);
		CheckCompileErrors(fragmentId, GL_FRAGMENT_SHADER, fragmentPath);
		if (geometryId != 0)
			CheckCompileErrors(geometryId, GL_GEOMETRY_SHADER, geometryPath);
//#endif

		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexId);
		glAttachShader(programID, fragmentId);
		if (geometryId != 0)
			glAttachShader(programID, geometryId);

		glLinkProgram(programID);
//#if !defined(_RELEASE)
		CheckLinkErrors(programID);
//#endif

		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		if (!geometryPath.empty())
			glDeleteShader(geometryId);

		return programID;
	}

	std::string OpenGL_ShaderLoader::RetrieveCode(const std::string& path, std::string includeIndentifier)
	{
		includeIndentifier += ' ';

		std::string sourceCode = "";
		std::ifstream file(path);
		
		if (!file.is_open())
		{
			JERBOA_LOG_ERROR("ERROR: could not open the shader at: {}", path);
			return sourceCode;
		}

		std::string lineBuffer;
		while (std::getline(file, lineBuffer))
		{
			bool isInclude = lineBuffer.compare(0, includeIndentifier.length(), includeIndentifier) == 0;
			if (isInclude)
			{
				auto includePath = GetIncludePath(lineBuffer, includeIndentifier, path);
				sourceCode += RetrieveCode(includePath);
			}
			else {
				sourceCode += lineBuffer + '\n';
			}
		}

		file.close();

		return sourceCode;
	}

	std::string OpenGL_ShaderLoader::GetIncludePath(const std::string& lineBuffer, const std::string& includeIndentifier, const std::string& shaderPath) {
		std::string includeLine = lineBuffer;
		includeLine.erase(0, includeIndentifier.size());

		if (includeLine.front() == '<' && includeLine.back() == '>') {
			includeLine = SHADER_LIB_PATH + includeLine.substr(1, includeLine.size() - 2); // -2 because last character is '\0'
		}
		else {
			std::string folderPath = shaderPath;
			std::string slash = "/\\";
			size_t posSlash = folderPath.find_last_of(slash);
			folderPath.erase(posSlash, std::string::npos);

			std::string upOneLevel = "../";
			size_t posUpOneLevel = includeLine.find(upOneLevel);
			while (posUpOneLevel != std::string::npos) {
				includeLine.erase(0, upOneLevel.length());
				posUpOneLevel = includeLine.find(upOneLevel);

				posSlash = folderPath.find_last_of(slash);
				folderPath.erase(posSlash, std::string::npos);
			}

			includeLine = folderPath + "/" + includeLine;
		}

		return includeLine;
	}

	unsigned int OpenGL_ShaderLoader::CreateAndCompileShader(std::string shaderCode, GLenum shaderType) {
		const char* gShaderCode = shaderCode.c_str();
		unsigned int shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &gShaderCode, NULL);
		glCompileShader(shaderID);

		return shaderID;
	}

	void OpenGL_ShaderLoader::CheckCompileErrors(GLuint shader, GLenum shaderType, const std::string& shaderPath)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			JERBOA_LOG_ERROR("SHADER_COMPILATION_ERROR \nPath: {0}\nErrors: {1}", shaderPath, infoLog);
		}
	}

	void OpenGL_ShaderLoader::CheckLinkErrors(GLuint program)
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
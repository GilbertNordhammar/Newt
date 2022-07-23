#include "jerboa-pch.h"
#include "GL_ShaderLoader.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Core/String.h"

#include <filesystem>
#include <algorithm>

namespace Jerboa
{
	static const std::string CURRENT_DIR_PATH = std::filesystem::current_path().string() + "/";

	GLuint GL_ShaderLoader::Load(
		const std::string &vertexPath,
		const std::string &fragmentPath,
		const std::string &geometryPath)
	{
		JERBOA_LOG_INFO("Loading shader from files:\n - Vertex: {0}\n - Fragment: {1}\n - Geometry: {2}",
						vertexPath, fragmentPath, geometryPath.empty() ? "<None>" : geometryPath);

		std::string vertexCode = GetShaderCode(vertexPath);
		std::string fragmentCode = GetShaderCode(fragmentPath);
		std::string geometryCode;
		if (!geometryPath.empty())
			geometryCode = GetShaderCode(geometryPath);

		return CreateShader(vertexCode, fragmentCode, geometryCode);
	}

	GLuint GL_ShaderLoader::Load(const std::string &path)
	{
		JERBOA_LOG_INFO("Loading shader from \"{0}\"", path);

		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;

		std::ifstream file(path);

		if (!file.is_open())
		{
			JERBOA_LOG_ERROR("ERROR: could not open the shader at: {}", path);
		}

		std::string absPath = CURRENT_DIR_PATH + path;
		while (!file.eof())
		{
			auto shaderType = IdentifyShaderType(file);
			std::vector<std::string> accumulatedPaths;
			switch (shaderType)
			{
			case ShaderType::Vertex:
				vertexCode = GetShaderCode(file, absPath, accumulatedPaths, "#end vertex");
				break;
			case ShaderType::Fragment:
				fragmentCode = GetShaderCode(file, absPath, accumulatedPaths, "#end fragment");
				break;
			case ShaderType::Geometry:
				geometryCode = GetShaderCode(file, absPath, accumulatedPaths, "#end geometry");
				break;
			default:
				JERBOA_LOG_ERROR("Missing or invalid shader type declaration in {0}", path);
				break;
			}
		}

		file.close();

		return CreateShader(vertexCode, fragmentCode, geometryCode);
	}

	GLuint GL_ShaderLoader::CreateShader(const std::string &vertexCode, const std::string &fragmentCode, const std::string &geometryCode)
	{
		unsigned int vertexId = CreateComponentShader(vertexCode, GL_VERTEX_SHADER);
		unsigned int fragmentId = CreateComponentShader(fragmentCode, GL_FRAGMENT_SHADER);
		unsigned int geometryId = 0;
		if (!geometryCode.empty())
		{
			geometryId = CreateComponentShader(geometryCode, GL_GEOMETRY_SHADER);
		}

		GLuint programID = CreateShaderProgram(vertexId, fragmentId, geometryId);

		CheckLinkErrors(programID);
		CheckCompileErrors(vertexId, "vertex");
		CheckCompileErrors(fragmentId, "fragment");
		if (geometryId != 0)
			CheckCompileErrors(geometryId, "geometry");

		DeleteShaders(vertexId, fragmentId, geometryId);

		return programID;
	}

	ShaderType GL_ShaderLoader::IdentifyShaderType(std::ifstream &file)
	{
		ShaderType shaderType = ShaderType::None;

		std::string line;

		do
		{
			std::getline(file, line);
			line = String::Trim(line, " \t");
		} while (!file.eof() && line.size() == 0);

		if (!file.eof())
		{
			if (line == "#begin vertex")
				shaderType = ShaderType::Vertex;
			else if (line == "#begin fragment")
				shaderType = ShaderType::Fragment;
			else if (line == "#begin geometry")
				shaderType = ShaderType::Geometry;
		}

		return shaderType;
	}

	std::string GL_ShaderLoader::GetShaderCode(
		std::ifstream &file, const std::string &absPath,
		std::vector<std::string> &out_accumulatedPaths, const std::string &endOfShaderIdentifier)
	{
		bool alreadyParsed = std::find(out_accumulatedPaths.begin(), out_accumulatedPaths.end(), absPath) != out_accumulatedPaths.end();
		if (!alreadyParsed)
			out_accumulatedPaths.push_back(absPath);

		std::string sourceCode;
		std::string line;

		while (std::getline(file, line))
		{
			if (!endOfShaderIdentifier.empty())
			{
				bool endOfShader = String::Trim(line, " \t").compare(0, endOfShaderIdentifier.size(), endOfShaderIdentifier) == 0;
				if (endOfShader)
				{
					break;
				}
			}

			char includeIdentifier[] = "#include ";
			int length = sizeof(includeIdentifier) / sizeof(char) - 1;
			bool isInclude = line.compare(0, length, includeIdentifier) == 0;
			if (isInclude)
			{
				line = String::Trim(line, " \t");
				auto includePath = GetIncludePath(line, includeIdentifier, absPath);

				bool alreadyIncluded = std::find(out_accumulatedPaths.begin(), out_accumulatedPaths.end(), includePath) != out_accumulatedPaths.end();
				if (!alreadyIncluded)
				{
					std::ifstream includeFile(includePath);
					if (!includeFile.is_open())
					{
						JERBOA_LOG_ERROR("Could not open included file at line \"{0}\"", line);
					}

					sourceCode += GetShaderCode(includeFile, includePath, out_accumulatedPaths, endOfShaderIdentifier);
					includeFile.close();
				}
			}
			else
			{
				sourceCode += line + '\n';
			}
		}

		return sourceCode;
	}

	std::string GL_ShaderLoader::GetShaderCode(const std::string &path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			JERBOA_LOG_ERROR("Could not open the shader at {}", path);
		}

		std::vector<std::string> accumulatedPaths;
		std::string code = GetShaderCode(file, path, accumulatedPaths);

		file.close();

		return code;
	}

	GLuint GL_ShaderLoader::CreateShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId, GLuint geometryShaderId)
	{
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderId);
		glAttachShader(programID, fragmentShaderId);
		if (geometryShaderId != 0)
			glAttachShader(programID, geometryShaderId);

		glLinkProgram(programID);

		return programID;
	}

	void GL_ShaderLoader::DeleteShaders(GLuint vertexShaderId, GLuint fragmentShaderId, GLuint geometryShaderId)
	{
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		if (geometryShaderId != 0)
			glDeleteShader(geometryShaderId);
	}

	std::string GL_ShaderLoader::GetIncludePath(const std::string &lineBuffer, const std::string &includeIndentifier, const std::string &shaderPath)
	{
		std::string includeLine = lineBuffer;
		includeLine.erase(0, includeIndentifier.size());

		char shaderLibPath[256];
		strcpy(shaderLibPath, CURRENT_DIR_PATH.c_str());
		strcat(shaderLibPath, "assets/shaders/Jerboa/");
		if (includeLine.front() == '<' && includeLine.back() == '>')
		{
			includeLine = shaderLibPath + includeLine.substr(1, includeLine.size() - 2); // -2 because last character is '\0'
		}
		else
		{
			std::string folderPath = shaderPath;
			std::string slash = "/\\";
			size_t posSlash = folderPath.find_last_of(slash);
			folderPath.erase(posSlash, std::string::npos);

			std::string upOneLevel = "../";
			size_t posUpOneLevel = includeLine.find(upOneLevel);
			while (posUpOneLevel != std::string::npos)
			{
				includeLine.erase(0, upOneLevel.length());
				posUpOneLevel = includeLine.find(upOneLevel);

				posSlash = folderPath.find_last_of(slash);
				folderPath.erase(posSlash, std::string::npos);
			}

			includeLine = folderPath + "/" + includeLine;
		}

		return includeLine;
	}

	GLuint GL_ShaderLoader::CreateComponentShader(const std::string &shaderCode, GLenum shaderType)
	{
		const char *gShaderCode = shaderCode.c_str();
		auto shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &gShaderCode, NULL);
		glCompileShader(shaderID);

		return shaderID;
	}

	void GL_ShaderLoader::CheckCompileErrors(GLuint shader, const std::string &shaderType)
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

	void GL_ShaderLoader::CheckLinkErrors(GLuint program)
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
} // namespace Jerboa
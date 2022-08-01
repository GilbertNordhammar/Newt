#include "jerboa-pch.h"

#include "ShaderLoaderGLSL.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Core/String.h"

#include <filesystem>

namespace Jerboa
{
	static const std::string CURRENT_DIR_PATH = std::filesystem::current_path().string() + "/";

	ShaderDataGLSL ShaderLoaderGLSL::Load(
		const std::string& vertexPath,
		const std::string& fragmentPath)
	{
		JERBOA_LOG_INFO("Loading shader from files:\n - Vertex: {0}\n - Fragment: {1}", vertexPath, fragmentPath);

		std::string vertexCode = LoadCode(vertexPath);
		std::string fragmentCode = LoadCode(fragmentPath);

		return ShaderDataGLSL(ShaderSource(LoadCode(vertexPath)), ShaderSource(LoadCode(fragmentPath)));
	}

	ShaderDataGLSL ShaderLoaderGLSL::Load(const std::string& path)
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
				vertexCode = LoadCode(file, absPath, accumulatedPaths, "#end vertex");
				break;
			case ShaderType::Fragment:
				fragmentCode = LoadCode(file, absPath, accumulatedPaths, "#end fragment");
				break;
			default:
				JERBOA_LOG_ERROR("Missing or invalid shader type declaration in {0}", path);
				break;
			}
		}

		file.close();

		return ShaderDataGLSL(ShaderSource(vertexCode), ShaderSource(fragmentCode));
	}

	ShaderType ShaderLoaderGLSL::IdentifyShaderType(std::ifstream& file)
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
		}

		return shaderType;
	}

	std::string ShaderLoaderGLSL::LoadCode(
		std::ifstream& file, const std::string& absPath,
		std::vector<std::string>& out_accumulatedPaths, const std::string& endOfShaderIdentifier)
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
				auto includePath = LoadInclude(line, includeIdentifier, absPath);

				bool alreadyIncluded = std::find(out_accumulatedPaths.begin(), out_accumulatedPaths.end(), includePath) != out_accumulatedPaths.end();
				if (!alreadyIncluded)
				{
					std::ifstream includeFile(includePath);
					if (!includeFile.is_open())
					{
						JERBOA_LOG_ERROR("Could not open included file at line \"{0}\"", line);
					}

					sourceCode += LoadCode(includeFile, includePath, out_accumulatedPaths, endOfShaderIdentifier);
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

	std::string ShaderLoaderGLSL::LoadCode(const std::string& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			JERBOA_LOG_ERROR("Could not open the shader at {}", path);
		}

		std::vector<std::string> accumulatedPaths;
		std::string code = LoadCode(file, path, accumulatedPaths);

		file.close();

		return code;
	}

	std::string ShaderLoaderGLSL::LoadInclude(const std::string& lineBuffer, const std::string& includeIndentifier, const std::string& shaderPath)
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
}

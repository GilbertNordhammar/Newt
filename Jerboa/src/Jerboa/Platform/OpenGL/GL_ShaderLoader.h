#pragma once

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include <string>
#include <fstream>
#include <vector>

namespace Jerboa
{
	enum class ShaderType
	{
		None,
		Vertex,
		Fragment,
		Geometry
	};

	class GL_ShaderLoader
	{
	public:
		// Return the source code of the complete shader
		static GLuint Load(
			const std::string &vertexPath,
			const std::string &fragmentPath,
			const std::string &geometryPath);

		static GLuint Load(const std::string &path);

	private:
		static GLuint CreateShader(
			const std::string &vertexCode,
			const std::string &fragmentCode,
			const std::string &geometryCode);

		static GLuint CreateShaderProgram(
			GLuint vertexShaderId,
			GLuint fragmentShaderId,
			GLuint geometryShaderId = 0);
		static GLuint CreateComponentShader(const std::string &shaderCode, GLenum shaderType);

		static ShaderType IdentifyShaderType(std::ifstream &file);

		static std::string GetShaderCode(
			std::ifstream &file, const std::string &absPath,
			std::vector<std::string> &out_accumulatedPaths, const std::string &endOfShaderIdentifier = "");
		static std::string GetShaderCode(const std::string &path);
		static std::string GetIncludePath(const std::string &lineBuffer, const std::string &includeIndentifier, const std::string &shaderPath);

		static void DeleteShaders(GLuint vertexShaderId,
								  GLuint fragmentShaderId,
								  GLuint geometryShaderId = 0);

		static void CheckCompileErrors(GLuint shader, const std::string &shaderPath);
		static void CheckLinkErrors(GLuint program);
	};
} // namespace Jerboa

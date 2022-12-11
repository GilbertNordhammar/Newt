#pragma once

#include "Jerboa/Rendering/Resource/Data/ShaderDataGLSL.h"

#include <string>
#include <vector>

namespace Jerboa
{
	enum class ShaderType
	{
		None,
		Vertex,
		Fragment
	};

	class ShaderLoaderGLSL
	{
	public:
		static ShaderDataGLSL Load(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);
		static ShaderDataGLSL Load(const std::string& path);

	private:
		static ShaderType IdentifyShaderType(std::ifstream& file);
		static std::string LoadCode(
			std::ifstream& file, const std::string& absPath,
			std::vector<std::string>& out_accumulatedPaths, const std::string& endOfShaderIdentifier = "");
		static std::string LoadCode(const std::string& path);
		static std::string LoadInclude(const std::string& lineBuffer, const std::string& includeIndentifier, const std::string& shaderPath);
	};	
}
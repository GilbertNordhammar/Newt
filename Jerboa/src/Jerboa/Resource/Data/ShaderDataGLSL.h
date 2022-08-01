#pragma once

#include <string>

namespace Jerboa
{
	class ShaderSource
	{
	public:
		ShaderSource(const std::string& sourceCode)
			: m_SourceCode(sourceCode)
		{
		}

		const std::string& GetCode() const { return m_SourceCode; }
	private:
		std::string m_SourceCode;
	};

	class ShaderDataGLSL
	{
	public:
		ShaderDataGLSL(const std::string& vertexName, const ShaderSource& vertexSource, const std::string& fragmentName, const ShaderSource& fragmentSource)
			: m_VertexName(vertexName), m_VertexSource(vertexSource), m_FragmentName(fragmentName), m_FragmentSource(fragmentSource)
		{
		}

		const std::string& GetVertexName() const { return m_VertexName; }
		const std::string& GetFragmentName() const { return m_FragmentName; }
		const ShaderSource& GetVertexSource() const { return m_VertexSource; }
		const ShaderSource& GetFragmentSource() const { return m_FragmentSource; }

	private:
		std::string m_VertexName = "";
		std::string m_FragmentName = "";
		ShaderSource m_VertexSource;
		ShaderSource m_FragmentSource;
	};
}

#pragma once

#include <string>
#include <string_view>

namespace Jerboa
{
	class ShaderSource
	{
	public:
		ShaderSource(const std::string& sourceCode)
			: m_SourceCode(sourceCode)
		{
		}

		const std::string& GetSourceCode() const { return m_SourceCode; }
	private:
		std::string m_SourceCode;
	};

	class ShaderDataGLSL
	{
	public:
		ShaderDataGLSL(const ShaderSource& vertexSource, const ShaderSource& fragmentSource)
			: m_VertexSource(vertexSource), m_FragmentSource(fragmentSource)
		{
		}

		const ShaderSource& GetVertexCode() const { return m_VertexSource; }
		const ShaderSource& GetFragmentCode() const { return m_FragmentSource; }

	private:
		ShaderSource m_VertexSource;
		ShaderSource m_FragmentSource;
	};
}

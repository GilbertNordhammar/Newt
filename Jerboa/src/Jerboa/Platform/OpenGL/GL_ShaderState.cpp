#include "jerboa-pch.h"
#include "GL_ShaderState.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Platform/OpenGL/GL_RenderState.h"

namespace Jerboa
{
	GL_ShaderState::GL_ShaderState(GL_RenderState* renderState)
		: m_RenderStateGL(renderState)
	{
	}

	void GL_ShaderState::SetBool(const std::string& name, bool value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform1i(glGetUniformLocation(shaderResource, name.c_str()), (int)value);
	}

	void GL_ShaderState::SetInt(const std::string& name, int value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform1i(glGetUniformLocation(shaderResource, name.c_str()), value);
	}

	void GL_ShaderState::SetFloat(const std::string& name, float value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform1f(glGetUniformLocation(shaderResource, name.c_str()), value);
	}

	void GL_ShaderState::SetVec2(const std::string& name, const glm::vec2& value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform2fv(glGetUniformLocation(shaderResource, name.c_str()), 1, &value[0]);
	}

	void GL_ShaderState::SetVec2(const std::string& name, float x, float y)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform2f(glGetUniformLocation(shaderResource, name.c_str()), x, y);
	}

	void GL_ShaderState::SetVec3(const std::string& name, const glm::vec3& value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform3fv(glGetUniformLocation(shaderResource, name.c_str()), 1, &value[0]);
	}

	void GL_ShaderState::SetVec3(const std::string& name, float x, float y, float z)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform3f(glGetUniformLocation(shaderResource, name.c_str()), x, y, z);
	}

	void GL_ShaderState::SetVec4(const std::string& name, const glm::vec4& value)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform4fv(glGetUniformLocation(shaderResource, name.c_str()), 1, &value[0]);
	}

	void GL_ShaderState::SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniform4f(glGetUniformLocation(shaderResource, name.c_str()), x, y, z, w);
	}

	void GL_ShaderState::SetMat2(const std::string& name, const glm::mat2& mat)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniformMatrix2fv(glGetUniformLocation(shaderResource, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GL_ShaderState::SetMat3(const std::string& name, const glm::mat3& mat)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniformMatrix3fv(glGetUniformLocation(shaderResource, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GL_ShaderState::SetMat4(const std::string& name, const glm::mat4& mat)
	{
		uint64 shaderResource = m_RenderStateGL->GetBoundShader()->GetGPUResource().Get();
		glUniformMatrix4fv(glGetUniformLocation(shaderResource, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
}
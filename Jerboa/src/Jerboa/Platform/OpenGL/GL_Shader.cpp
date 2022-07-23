#include "jerboa-pch.h"
#include "GL_Shader.h"

#include "GL_ShaderLoader.h"

namespace Jerboa
{
	GL_Shader::GL_Shader(
		const std::string &vertexPath,
		const std::string &fragmentPath,
		const std::string &geometryPath)
		: mVertexPath(vertexPath), mFragmentPath(fragmentPath), mGeometryPath(geometryPath)
	{
		mProgramID = GL_ShaderLoader::Load(vertexPath, fragmentPath, geometryPath);
		//ShaderGlobals::Get().LinkGlobals(mProgramID);
	}

	GL_Shader::GL_Shader(const std::string &path)
	{
		mProgramID = GL_ShaderLoader::Load(path);
	}

	GL_Shader::GL_Shader(const GL_Shader &other)
		: GL_Shader(other.mVertexPath, other.mFragmentPath, other.mGeometryPath) {}

	GL_Shader::GL_Shader(GL_Shader &&other) noexcept : mVertexPath(other.mVertexPath),
													   mFragmentPath(other.mFragmentPath),
													   mGeometryPath(other.mGeometryPath),
													   mProgramID(other.mProgramID)
	{
		other.mProgramID = 0;
	}

	GL_Shader &GL_Shader::operator=(GL_Shader other)
	{
		Swap(*this, other);

		return *this;
	}

	void GL_Shader::Swap(GL_Shader &first, GL_Shader &second) noexcept
	{
		using std::swap;

		swap(first.mProgramID, second.mProgramID);
		swap(first.mVertexPath, second.mVertexPath);
		swap(first.mFragmentPath, second.mFragmentPath);
		swap(first.mGeometryPath, second.mGeometryPath);
	}

	GL_Shader::~GL_Shader()
	{
		glDeleteProgram(mProgramID);
	}

	void GL_Shader::Bind()
	{
		glUseProgram(mProgramID);
	}

	void GL_Shader::SetBool(const std::string &name, bool value)
	{
		glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), (int)value);
	}

	void GL_Shader::SetInt(const std::string &name, int value)
	{
		glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), value);
	}

	void GL_Shader::SetFloat(const std::string &name, float value)
	{
		glUniform1f(glGetUniformLocation(mProgramID, name.c_str()), value);
	}

	void GL_Shader::SetVec2(const std::string &name, const glm::vec2 &value)
	{
		glUniform2fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void GL_Shader::SetVec2(const std::string &name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(mProgramID, name.c_str()), x, y);
	}

	void GL_Shader::SetVec3(const std::string &name, const glm::vec3 &value)
	{
		glUniform3fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void GL_Shader::SetVec3(const std::string &name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(mProgramID, name.c_str()), x, y, z);
	}

	void GL_Shader::SetVec4(const std::string &name, const glm::vec4 &value)
	{
		glUniform4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void GL_Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(mProgramID, name.c_str()), x, y, z, w);
	}

	void GL_Shader::SetMat2(const std::string &name, const glm::mat2 &mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GL_Shader::SetMat3(const std::string &name, const glm::mat3 &mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GL_Shader::SetMat4(const std::string &name, const glm::mat4 &mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
} // namespace Jerboa
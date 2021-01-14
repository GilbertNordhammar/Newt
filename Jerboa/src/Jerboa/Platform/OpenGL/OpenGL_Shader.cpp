#include "jerboa-pch.h"
#include "OpenGL_Shader.h"

#include "OpenGL_ShaderLoader.h"

namespace Jerboa {
	OpenGL_Shader::OpenGL_Shader(
		const std::string& vertexPath,
		const std::string& fragmentPath,
		const std::string& geometryPath)
		: mVertexPath(vertexPath), mFragmentPath(fragmentPath), mGeometryPath(geometryPath)
	{
		mProgramID = OpenGL_ShaderLoader::Load(vertexPath, fragmentPath, geometryPath);
		//ShaderGlobals::Get().LinkGlobals(mProgramID);
	}

	OpenGL_Shader::OpenGL_Shader(const std::string& path)
	{
		mProgramID = OpenGL_ShaderLoader::Load(path);
	}

	OpenGL_Shader::OpenGL_Shader(const OpenGL_Shader& other)
		: OpenGL_Shader(other.mVertexPath, other.mFragmentPath, other.mGeometryPath) {}

	OpenGL_Shader::OpenGL_Shader(OpenGL_Shader&& other) noexcept :
		mVertexPath(other.mVertexPath),
		mFragmentPath(other.mFragmentPath),
		mGeometryPath(other.mGeometryPath),
		mProgramID(other.mProgramID)
	{
		other.mProgramID = 0;
	}

	OpenGL_Shader& OpenGL_Shader::operator=(OpenGL_Shader other) {
		Swap(*this, other);

		return *this;
	}

	void OpenGL_Shader::Swap(OpenGL_Shader& first, OpenGL_Shader& second) noexcept {
		using std::swap;

		swap(first.mProgramID, second.mProgramID);
		swap(first.mVertexPath, second.mVertexPath);
		swap(first.mFragmentPath, second.mFragmentPath);
		swap(first.mGeometryPath, second.mGeometryPath);
	}

	OpenGL_Shader::~OpenGL_Shader() {
		glDeleteProgram(mProgramID);
	}

	void OpenGL_Shader::Bind()
	{
		glUseProgram(mProgramID);
	}

	void OpenGL_Shader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), (int)value);
	}

	void OpenGL_Shader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), value);
	}

	void OpenGL_Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(mProgramID, name.c_str()), value);
	}

	void OpenGL_Shader::SetVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void OpenGL_Shader::SetVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(mProgramID, name.c_str()), x, y);
	}

	void OpenGL_Shader::SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void OpenGL_Shader::SetVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(mProgramID, name.c_str()), x, y, z);
	}

	void OpenGL_Shader::SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, &value[0]);
	}
	void OpenGL_Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(mProgramID, name.c_str()), x, y, z, w);
	}

	void OpenGL_Shader::SetMat2(const std::string& name, const glm::mat2& mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void OpenGL_Shader::SetMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void OpenGL_Shader::SetMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
}
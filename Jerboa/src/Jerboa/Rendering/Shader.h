#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace Jerboa {
	class Shader
	{
	public:
		static std::shared_ptr<Shader> Create(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);
        static std::shared_ptr<Shader> Shader::Create(const std::string& path);

		virtual void Bind() = 0;

        virtual void SetBool(const std::string& name, bool value) = 0;
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetVec2(const std::string& name, float x, float y) = 0;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetVec3(const std::string& name, float x, float y, float z) = 0;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetVec4(const std::string& name, float x, float y, float z, float w) = 0;
        virtual void SetMat2(const std::string& name, const glm::mat2& mat) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& mat) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& mat) = 0;
	};
}
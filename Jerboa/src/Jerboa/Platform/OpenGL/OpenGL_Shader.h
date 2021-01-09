#pragma once

#include "Jerboa/Rendering/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace Jerboa {
    class OpenGL_Shader : public Shader
    {
    public:
        OpenGL_Shader(const std::string& vertexPath,
            const std::string& fragmentPath,
            const std::string& geometryPath = "");

        OpenGL_Shader(const OpenGL_Shader& other);
        OpenGL_Shader(OpenGL_Shader&& other) noexcept;
        ~OpenGL_Shader();

        OpenGL_Shader& operator=(OpenGL_Shader other);

        virtual void Use() const override;

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec2(const std::string& name, float x, float y) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w);
        void SetMat2(const std::string& name, const glm::mat2& mat) const;
        void SetMat3(const std::string& name, const glm::mat3& mat) const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;

        GLuint GetProgramID() const { return mProgramID; }
        const std::string& GetVertexPath() const { return mVertexPath; }
        const std::string& GetFragmentPath() const { return mFragmentPath; }
        const std::string& GetGeometryPath() const { return mGeometryPath; }

    private:
        GLuint mProgramID;
        std::string mVertexPath;
        std::string mFragmentPath;
        std::string mGeometryPath;

        void Swap(OpenGL_Shader& first, OpenGL_Shader& second) noexcept;
    };
}

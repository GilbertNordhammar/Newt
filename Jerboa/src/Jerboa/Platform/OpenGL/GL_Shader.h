#pragma once

#include "Jerboa/Rendering/Shader.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include <glm/glm.hpp>
#include <string>

namespace Jerboa
{
    class GL_Shader : public Shader
    {
    public:
        GL_Shader(const std::string &vertexPath,
                  const std::string &fragmentPath,
                  const std::string &geometryPath = "");
        GL_Shader(const std::string &path);

        GL_Shader(const GL_Shader &other);
        GL_Shader(GL_Shader &&other) noexcept;
        ~GL_Shader();

        GL_Shader &operator=(GL_Shader other);

        virtual void Bind() override;

        virtual void SetBool(const std::string &name, bool value) override;
        virtual void SetInt(const std::string &name, int value) override;
        virtual void SetFloat(const std::string &name, float value) override;
        virtual void SetVec2(const std::string &name, const glm::vec2 &value) override;
        virtual void SetVec2(const std::string &name, float x, float y) override;
        virtual void SetVec3(const std::string &name, const glm::vec3 &value) override;
        virtual void SetVec3(const std::string &name, float x, float y, float z) override;
        virtual void SetVec4(const std::string &name, const glm::vec4 &value) override;
        virtual void SetVec4(const std::string &name, float x, float y, float z, float w) override;
        virtual void SetMat2(const std::string &name, const glm::mat2 &mat) override;
        virtual void SetMat3(const std::string &name, const glm::mat3 &mat) override;
        virtual void SetMat4(const std::string &name, const glm::mat4 &mat) override;

        GLuint GetProgramID() const { return mProgramID; }
        const std::string &GetVertexPath() const { return mVertexPath; }
        const std::string &GetFragmentPath() const { return mFragmentPath; }
        const std::string &GetGeometryPath() const { return mGeometryPath; }

    private:
        GLuint mProgramID;
        std::string mVertexPath;
        std::string mFragmentPath;
        std::string mGeometryPath;

        void Swap(GL_Shader &first, GL_Shader &second) noexcept;
    };
} // namespace Jerboa

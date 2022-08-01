#pragma once

#include "Jerboa/Rendering/ShaderState.h"

namespace Jerboa
{
    class GL_RenderState;

    class GL_ShaderState : public ShaderState
    {
    public:
        GL_ShaderState(GL_RenderState* renderState);

        void SetBool(const std::string& name, bool value) override;
        void SetInt(const std::string& name, int value) override;
        void SetFloat(const std::string& name, float value) override;
        void SetVec2(const std::string& name, const glm::vec2& value) override;
        void SetVec2(const std::string& name, float x, float y) override;
        void SetVec3(const std::string& name, const glm::vec3& value) override;
        void SetVec3(const std::string& name, float x, float y, float z) override;
        void SetVec4(const std::string& name, const glm::vec4& value) override;
        void SetVec4(const std::string& name, float x, float y, float z, float w) override;
        void SetMat2(const std::string& name, const glm::mat2& mat) override;
        void SetMat3(const std::string& name, const glm::mat3& mat) override;
        void SetMat4(const std::string& name, const glm::mat4& mat) override;
    private:
        GL_RenderState* m_RenderStateGL;
    };
}
#pragma once

#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include <glm/glm.hpp>

#include <memory>

namespace Jerboa
{
    class ShaderDataGLSL;
    class GPUResourceAllocator;

    class Shader
    {
    public:
        ~Shader();
        void Create(const ShaderDataGLSL& data, GPUResourceAllocator &allocator);
        const GPUResource &GetGPUResource() const { return m_GPUResource; }

    private:
        GPUResource m_GPUResource;
    };
}
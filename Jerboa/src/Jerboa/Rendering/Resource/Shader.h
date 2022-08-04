#pragma once

#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include <glm/glm.hpp>

#include <memory>

namespace Jerboa {
    class ShaderDataGLSL;
    class GPUResourceAllocator;

    class Shader
    {
    public:
        void Create(ShaderDataGLSL data, GPUResourceAllocator& allocator);
        GPUResource& GetGPUResource() { return m_GPUResource; }
    private:
        GPUResource m_GPUResource;
    };
}
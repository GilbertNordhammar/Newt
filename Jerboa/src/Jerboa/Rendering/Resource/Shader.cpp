#include "jerboa-pch.h"
#include "Shader.h"

#include "Jerboa/Resource/Data/ShaderDataGLSL.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa {
	void Shader::Create(ShaderDataGLSL data, GPUResourceAllocator& allocator)
	{
		m_GPUResource = allocator.CreateShader(data);
	}
}
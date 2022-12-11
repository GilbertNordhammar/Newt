#include "jerboa-pch.h"
#include "Shader.h"

#include "Jerboa/Core/EventBus.h"
#include "Jerboa/Rendering/Events/ShaderDestroyedEvent.h"
#include "Jerboa/Rendering/Resource/Data/ShaderDataGLSL.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa {
	Shader::~Shader()
	{
		EventBus::Publish(ShaderDestroyedEvent(*this));
	}

	void Shader::Create(const ShaderDataGLSL& data, GPUResourceAllocator& allocator)
	{
		m_GPUResource = allocator.CreateShader(data);
	}
}
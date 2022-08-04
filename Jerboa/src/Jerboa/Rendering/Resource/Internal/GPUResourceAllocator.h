#pragma once

#include "Jerboa/Core/Singleton.h"
#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Resource/Data/TextureData.h"
#include "Jerboa/Resource/Data/ShaderDataGLSL.h"

namespace Jerboa
{
	class GPUResourceAllocator : Singleton<GPUResourceAllocator>
	{
	public:
		virtual GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) = 0;
		virtual GPUResource CreateVertexArrayObject(); // Needed for OpenGL
		virtual GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) = 0;
		virtual GPUResource	CreateTexture(const TextureData& textureData) = 0;
		virtual GPUResource	CreateShader(const ShaderDataGLSL& shaderData) = 0;
	};
}

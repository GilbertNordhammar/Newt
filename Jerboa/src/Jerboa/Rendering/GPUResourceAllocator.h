#pragma once

#include "Jerboa/Core/Singleton.h"
#include "Jerboa/Rendering/GPUResource.h"
#include "Jerboa/Rendering/IndexBuffer.h"
#include "Jerboa/Rendering/VertexBuffer.h"
#include "Jerboa/Resource/Data/TextureData.h"

namespace Jerboa
{
	class GPUResourceAllocator : Singleton<GPUResourceAllocator>
	{
	public:
		virtual GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) = 0;
		virtual GPUResource CreateVertexArrayObject(); // Needed for OpenGL
		virtual GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) = 0;
		virtual GPUResource	CreateTexture(const TextureData& textureData) = 0;
	};
}

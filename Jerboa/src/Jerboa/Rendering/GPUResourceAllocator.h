#pragma once
#include "Jerboa/Rendering/GPUResource.h"
#include "Jerboa/Rendering/VertexBuffer.h"
#include "Jerboa/Rendering/IndexBuffer.h"

namespace Jerboa
{
	class GPUResourceAllocator
	{
	public:
		virtual GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) = 0;
		virtual GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) = 0;
		virtual GPUResource CreateVertexArrayObject(); // Needed for OpenGL
	};
	
}

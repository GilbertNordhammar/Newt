#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/OpenGL/GL_IndexBuffer.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/GPUResourceAllocator.h"

namespace Jerboa {
	void IndexBuffer::Create(IndexBufferData bufferData, GPUResourceAllocator* resourceAllocator)
	{
		m_IndexBufferResource = resourceAllocator->CreateIndexBuffer(bufferData);
		m_Size = bufferData.m_Size;
	}
}
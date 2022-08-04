#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa {
	void IndexBuffer::Create(IndexBufferData bufferData, GPUResourceAllocator* resourceAllocator)
	{
		m_IndexBufferResource = resourceAllocator->CreateIndexBuffer(bufferData);
		m_Size = bufferData.m_Size;
	}
}
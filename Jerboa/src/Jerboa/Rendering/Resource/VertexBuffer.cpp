#include "jerboa-pch.h"
#include "VertexBuffer.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Types.h";
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa {
	void VertexBuffer::Create(const VertexBufferData& bufferData, const GPUResourceAllocator& resourceAllocator)
	{
		m_GPUResource = resourceAllocator.CreateVertexBuffer(bufferData);
		m_Usage = bufferData.m_Usage;
		m_Layout = bufferData.m_Layout;
		m_Size = bufferData.m_Size;
	}

	VertexBuffer::VertexBuffer(uint32 size, VertexBufferUsage usage, VertexLayout layout)
		: m_Usage(usage), m_Layout(layout), m_Size(size)
	{
	}
}
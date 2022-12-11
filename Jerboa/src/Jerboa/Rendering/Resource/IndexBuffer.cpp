#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa {
	void IndexBuffer::Create(const IndexBufferData& bufferData, const GPUResourceAllocator& resourceAllocator)
	{
		m_GPUResource = resourceAllocator.CreateIndexBuffer(bufferData);
		m_Size = bufferData.GetDataByteSize();
	}
}
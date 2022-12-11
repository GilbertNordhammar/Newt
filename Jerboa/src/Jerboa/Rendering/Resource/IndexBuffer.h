#pragma once

#include <memory>
#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Resource/Data/IndexBufferData.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"

namespace Jerboa {
	class GPUResourceAllocator;
	struct IndexBufferData;

	class IndexBuffer
	{
	public:
		void Create(const IndexBufferData& bufferData, const GPUResourceAllocator& resourceAllocator);

		const GPUResource&		GetGPUResource() const { return m_GPUResource; }
		const uint32			GetSize() const { return m_Size; };
		const uint32			GetCount() const { return m_Size / sizeof(uint32); };

	protected:
		GPUResource m_GPUResource;
		uint32		m_Size = 0;
	};
}



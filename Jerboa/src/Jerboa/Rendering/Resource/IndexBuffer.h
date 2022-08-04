#pragma once

#include <memory>
#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"


namespace Jerboa {
	class GPUResourceAllocator;

	struct IndexBufferData
	{
		IndexBufferData(uint32* data, uint32_t size)
			: m_Data(data), m_Size(size)
		{
		}

		uint32* m_Data;
		uint32 m_Size;
	};

	class IndexBuffer
	{
	public:
		void Create(IndexBufferData bufferData, GPUResourceAllocator* resourceAllocator);

		virtual void	Bind() {};
		virtual void	Unbind() {};

		GPUResource&	GetGPUResource() { return m_GPUResource; }
		uint32_t		GetSize() const { return m_Size; };
		uint32_t		GetCount() const { return m_Size / sizeof(uint32_t); };

		virtual ~IndexBuffer() {};
	protected:
		GPUResource m_GPUResource;
		uint32_t m_Size = 0;
	};
}



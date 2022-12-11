#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Rendering/Types.h"

#include <vector>
#include <memory>
#include <initializer_list>

namespace Jerboa {
	class GPUResourceAllocator;

	struct VertexBufferData
	{
		VertexBufferData(VertexLayout layout)
			: m_Layout(layout)
		{
		}

		uint32 GetDataByteSize() const
		{ 
			return m_Data.size() * sizeof(float);
		}

		std::vector<float> m_Data;
		VertexBufferUsage m_Usage = VertexBufferUsage::Static;
		VertexLayout m_Layout;
	};
	
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;

		void Create(const VertexBufferData& bufferData, const GPUResourceAllocator& resourceAllocator);

		const GPUResource&			GetGPUResource() const { return m_GPUResource; }
		const VertexBufferUsage&	GetUsage() const { return m_Usage; };
		const VertexLayout&			GetLayout() const { return m_Layout; };
		uint32						GetSize() const { return m_Size; }
		uint32						GetCount() const { return m_Size / sizeof(float); }

	protected:
		VertexBuffer(uint32 size, VertexBufferUsage usage, VertexLayout layout);

		GPUResource m_GPUResource;
		VertexBufferUsage m_Usage;
		VertexLayout m_Layout;
		uint32 m_Size = 0;
	};
}



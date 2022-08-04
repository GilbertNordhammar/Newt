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
		VertexBufferData(float* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
			: m_Data(data), m_Size(size), m_Usage(usage), m_Layout(layout)
		{
		}

		float* m_Data;
		uint32 m_Size;
		VertexBufferUsage m_Usage;
		VertexBufferLayout m_Layout;
	};
	
	class VertexBuffer
	{
	public:
		void Create(const VertexBufferData& bufferData, GPUResourceAllocator* resourceAllocator);

		virtual void Bind() {};
		virtual void UnBind() {};

		GPUResource&				GetGPUResource() { return m_GPUResource; }
		const VertexBufferUsage&	GetUsage() const { return m_Usage; };
		const VertexBufferLayout&	GetLayout() const { return m_Layout; };
		uint32						GetSize() const { return m_Size; }
		uint32						GetCount() const { return m_Size / sizeof(float); }

		// Temp remove 
		VertexBuffer() = default;
		virtual ~VertexBuffer() {};
	protected:
		VertexBuffer(uint32 size, VertexBufferUsage usage, VertexBufferLayout layout);

		GPUResource m_GPUResource;
		VertexBufferUsage m_Usage;
		VertexBufferLayout m_Layout;
		uint32 m_Size = 0;
	};
}



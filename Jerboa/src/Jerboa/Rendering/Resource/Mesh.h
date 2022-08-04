#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"

#include <memory>

namespace Jerboa
{
	class GPUResourceAllocator;

	enum class PrimitiveType
	{
		Points,
		Lines,
		LineStrip,
		Triangle,
		TriangleStrip
	};

	class Mesh
	{
	public:
		~Mesh();
		void Create(const VertexBufferData& vertexBufferData, const IndexBufferData* indexBufferData, PrimitiveType primitiveType, GPUResourceAllocator* resourceAllocator);
		
		bool						IsIndexed() const;
		PrimitiveType				GetPrimitiveType() const { return m_PrimitiveType; }
		VertexBuffer*				GetVertexBuffer() { return &m_VertexBuffer; }
		IndexBuffer*				GetIndexBuffer() { return &m_IndexBuffer; }
		const GPUResource&			GetVAO() const { return m_VAO; }

	protected:
		GPUResource						m_VAO; // TODO: This is OpenGL specific. Find a way of hiding it from the general implementation
		VertexBuffer					m_VertexBuffer;
		IndexBuffer						m_IndexBuffer;
		PrimitiveType					m_PrimitiveType;
	};
}
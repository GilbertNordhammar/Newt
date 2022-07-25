#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/IndexBuffer.h"
#include "Jerboa/Rendering/VertexBuffer.h"

#include <memory>

#include "Jerboa/Platform/OpenGL/Objects/GL_VertexArrayObject.h";

namespace Jerboa
{
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

	struct IndexBufferData
	{
		IndexBufferData(uint32* data, uint32_t size)
			: m_Data(data), m_Size(size)
		{
		}

		uint32* m_Data;
		uint32 m_Size;
	};

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
		Mesh(const VertexBufferData& vertexBufferData, const IndexBufferData& indexBufferData, PrimitiveType primitiveType);
		
		void			Bind();
		bool			IsIndexed();
		uint32			GetVertexCount() const { return m_VertexBuffer->GetCount(); }
		uint32			GetIndexCount() const { return m_IndexBuffer->GetCount(); }
		PrimitiveType	GetPrimitiveType() const { return m_PrimitiveType; }

	private:
		std::shared_ptr<VertexBuffer>	m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer>	m_IndexBuffer = nullptr;
		PrimitiveType					m_PrimitiveType;

		GL_VertexArrayObject m_VAO;
	};
}
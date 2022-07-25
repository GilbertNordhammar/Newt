#include "jerboa-pch.h"
#include "Mesh.h"


namespace Jerboa
{
	Mesh::Mesh(const VertexBufferData& vertexBufferData, const IndexBufferData& indexBufferData, PrimitiveType primitiveType)
		: m_PrimitiveType(primitiveType)
	{
		glBindVertexArray(m_VAO);

		m_VertexBuffer = Jerboa::VertexBuffer::Create(vertexBufferData.m_Data, vertexBufferData.m_Size, vertexBufferData.m_Usage, vertexBufferData.m_Layout);
		m_IndexBuffer = Jerboa::IndexBuffer::Create(indexBufferData.m_Data, indexBufferData.m_Size);

		glBindVertexArray(0);
	}

	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}
	bool Mesh::IsIndexed()
	{
		return m_IndexBuffer != nullptr;
	}
}


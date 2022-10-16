#include "jerboa-pch.h"
#include "Mesh.h"

#include "Jerboa/Core/EventBus.h"
#include "Jerboa/Rendering/Events/MeshDestroyedEvent.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa
{
	Mesh::~Mesh()
	{
		EventBus::Publish(MeshDestroyedEvent(*this));
	}

	void SubMesh::Create(const VertexBufferData& vertexBufferData, const IndexBufferData* indexBufferData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator)
	{
		m_VAO = resourceAllocator.CreateVertexArrayObject();
		m_VertexBuffer.Create(vertexBufferData, resourceAllocator);
		if (indexBufferData)
			m_IndexBuffer.Create(*indexBufferData, resourceAllocator);
		m_PrimitiveType = primitiveType;
	}

	bool SubMesh::IsIndexed() const
	{
		return m_IndexBuffer.GetSize() > 0;
	}

	void Mesh::AddSubMesh(const VertexBufferData& vertexBufferData, const IndexBufferData* indexBufferData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator)
	{
		m_SubMeshes.emplace_back();
		m_SubMeshes.back().Create(vertexBufferData, indexBufferData, primitiveType, resourceAllocator);
	}

	void Mesh::RemoveSubMeshAtIndex(int i)
	{
		bool validIndex = i > 0 && i < m_SubMeshes.size();
		JERBOA_ASSERT(validIndex, "Given submesh index is out of range");
		if (validIndex)
		{
			m_SubMeshes.erase(m_SubMeshes.begin() + i);
		}
	}
}


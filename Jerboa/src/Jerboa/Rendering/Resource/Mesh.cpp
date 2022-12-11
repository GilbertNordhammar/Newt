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

	void SubMesh::Create(const SubMeshData& subMeshData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator)
	{
		m_VAO = resourceAllocator.CreateVertexArrayObject();
		m_VertexBuffer.Create(subMeshData.m_VertexBufferData, resourceAllocator);
		if (subMeshData.m_IndexBufferData.m_Data.size() > 0)
			m_IndexBuffer.Create(subMeshData.m_IndexBufferData, resourceAllocator);
		m_PrimitiveType = primitiveType;
	}

	bool SubMesh::IsIndexed() const
	{
		return m_IndexBuffer.GetSize() > 0;
	}

	void Mesh::Create(const MeshData& meshData, const GPUResourceAllocator& resourceAllocator)
	{
		m_SubMeshes.resize(meshData.m_SubMeshData.size());

		for (int i = 0; i < m_SubMeshes.size(); i++)
		{
			m_SubMeshes[i].Create(meshData.m_SubMeshData[i], PrimitiveType::Triangle, resourceAllocator); // TODO: Don't hard code primtive type
		}
	}

	void Mesh::AddSubMesh(const SubMeshData& subMeshData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator)
	{
		m_SubMeshes.emplace_back();
		m_SubMeshes.back().Create(subMeshData, primitiveType, resourceAllocator);
	}

	void Mesh::AddSubMesh(SubMesh&& subMesh)
	{
		m_SubMeshes.push_back(std::move(subMesh));
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


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

	void Mesh::Create(const VertexBufferData& vertexBufferData, const IndexBufferData* indexBufferData, PrimitiveType primitiveType, GPUResourceAllocator* resourceAllocator)
	{
		m_VAO = resourceAllocator->CreateVertexArrayObject();
		m_VertexBuffer.Create(vertexBufferData, resourceAllocator);
		if(indexBufferData)
			m_IndexBuffer.Create(*indexBufferData, resourceAllocator);
		m_PrimitiveType = primitiveType;
	}

	bool Mesh::IsIndexed() const
	{
		return m_IndexBuffer.GetSize() > 0;
	}
}


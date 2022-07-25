#include "jerboa-pch.h"
#include "Mesh.h"

#if defined(JERBOA_RENDER_API_OPENGL)
#include "Jerboa/Platform/OpenGL/GL_Mesh.h"
#endif

namespace Jerboa
{
	std::shared_ptr<Mesh> Mesh::Create(const VertexBufferData& vertexBufferData, const IndexBufferData& indexBufferData, PrimitiveType primitiveType)
	{
		std::shared_ptr<Mesh> mesh = nullptr;
	#if defined(JERBOA_RENDER_API_OPENGL)
		mesh = std::make_shared<GL_Mesh>(vertexBufferData, indexBufferData);
	#else
	#error "JERBOA_RENDER_API_ not defined"
	#endif

		JERBOA_ASSERT(mesh, "Mesh is null");
		JERBOA_ASSERT(mesh->m_VertexBuffer, "Vertex buffer is null");

		mesh->m_PrimitiveType = primitiveType;
		return mesh;
	}

	bool Mesh::IsIndexed() const
	{
		return m_IndexBuffer != nullptr;
	}
}


#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/Resource/Data/MeshData.h"
#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"

#include <memory>
#include <vector>

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

	class SubMesh
	{
	public:
		void						Create(const SubMeshData& subMeshData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator);
		bool						IsIndexed() const;
		PrimitiveType				GetPrimitiveType() const { return m_PrimitiveType; }
		const VertexBuffer*			GetVertexBuffer() const { return &m_VertexBuffer; }
		const IndexBuffer*			GetIndexBuffer() const { return &m_IndexBuffer; }
		const GPUResource&			GetVAO() const { return m_VAO; }

	private:
		GPUResource						m_VAO; // TODO: This is OpenGL specific. Find a way of hiding it from the general implementation
		VertexBuffer					m_VertexBuffer;
		IndexBuffer						m_IndexBuffer;
		PrimitiveType					m_PrimitiveType;
	};

	class Mesh
	{
	public:
		~Mesh();
		void						Create(const MeshData& meshData, const GPUResourceAllocator& resourceAllocator);
		void						AddSubMesh(const SubMeshData& subMeshData, PrimitiveType primitiveType, const GPUResourceAllocator& resourceAllocator);
		void						AddSubMesh(SubMesh&& subMesh);
		void						RemoveSubMeshAtIndex(int i);
		const std::vector<SubMesh>& GetSubMeshes() const { return m_SubMeshes; }
	private:
		std::vector<SubMesh> m_SubMeshes;
	};
}
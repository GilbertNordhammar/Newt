#pragma once

#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"

#include <memory>

namespace Jerboa
{
	struct SubMeshData
	{
		IndexBufferData m_IndexBufferData;
		VertexBufferData m_VertexBufferData;
	};

	struct MeshData
	{
		std::vector<SubMeshData> m_SubMeshData;
	};
}
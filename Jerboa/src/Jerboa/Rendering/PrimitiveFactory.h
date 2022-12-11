#pragma once

#include "Jerboa/Rendering/Resource/Data/MeshData.h"

#include <vector>
#include <glm/glm.hpp>


namespace Jerboa {
	class PrimitiveFactory
	{
	public:
		/*
			'rings' and 'segments' must be >= 3
			'out_vertices' will recieve data (position, uv, normal, tangent, bitangent) for each vertex
			'out_indices' will receive triangle indices (counter clock wise)
		*/
		static SubMeshData GenerateUVSphere(int rings, int segments, float radius, glm::vec2 uvScale);
	};
}



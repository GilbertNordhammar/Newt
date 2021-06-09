#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Jerboa::PrimitiveFactory {
	/*
		'rings' and 'segments' must be >= 3
		'out_vertices' will recieve data (position, uv, normal, tangent, bitangent) for each vertex
		'out_indices' will receive triangle indices (counter clock wise)
	*/
	void GenerateUVSphere(int rings, int segments, float radius, glm::vec2 uvScale, std::vector<float>& out_vertices, std::vector<uint32_t>& out_indices);
}



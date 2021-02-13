#pragma once

#include <vector>

namespace Jerboa::PrimitiveFactory {
	/*
		'rings' and 'segments' must be >= 3
		'out_vertices' will recieve position, texture coordinates and normal (in that order) for each vertex
		'out_indices' will recieve triangle indices (counter clock wise)
	*/
	void GenerateUVSphere(int rings, int segments, float radius, std::vector<float>& out_vertices, std::vector<uint32_t>& out_indices);
}



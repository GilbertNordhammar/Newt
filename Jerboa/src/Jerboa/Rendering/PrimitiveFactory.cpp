#include "jerboa-pch.h"
#include "PrimitiveFactory.h"

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace Jerboa::PrimitiveFactory {
	void GenerateUVSphere(int nRings, int nSegments, std::vector<float>& out_vertices, std::vector<uint32_t>& out_indices)
	{
		const int MIN_RINGS = 3, MIN_SEGMENTS = 3;

		JERBOA_ASSERT(nRings >= MIN_RINGS, "A UV sphere can't have less than 3 rings");
		JERBOA_ASSERT(nSegments >= MIN_SEGMENTS, "A UV sphere can't have less than 3 segments");

		/* Generating vertices */
		int nVertices = (nRings + 1) * (nSegments + 1);
		int nVertexDatas = nVertices * (3 + 2 + 3); // nVertices * (pos + UV + normal)
		out_vertices.resize(0);
		out_vertices.reserve(nVertexDatas);

		float segmentStep = (2 * glm::pi<float>()) / nSegments;
		float ringStep = glm::pi<float>() / nRings;
		for (int i = 0; i <= nRings; i++) {
			float ringAngle = glm::pi<float>() / 2 - i * ringStep;
			glm::vec3 pos;
			pos.y = glm::sin(ringAngle);
			float xz = glm::cos(ringAngle);
			
			for (int j = 0; j <= nSegments; j++) {
				float segmentAngle = 2 * glm::pi<float>() - j * segmentStep;
				pos.z = xz * glm::sin(segmentAngle);
				pos.x = xz * glm::cos(segmentAngle);

				glm::vec2 texCoord = { (float)j / nSegments, 1 - (float)i / nRings };
				glm::vec3 normal = pos;
				out_vertices.insert(out_vertices.end(), { pos.x, pos.y, pos.z, texCoord.x, texCoord.y, normal.x, normal.y, normal.z });
			}
		}

		/* Generting indices */
		int nExtraRings = nRings - MIN_RINGS;
		int nTriangles = nRings * nSegments + (1 + nExtraRings) * nSegments;
		int nIndices = 3 * nTriangles;
		out_indices.resize(0);
		out_indices.reserve(nIndices);

		for (int i = 0; i < nRings; ++i)
		{
			uint32_t k1 = i * (nSegments + 1); // beginning of current ring
			uint32_t k2 = k1 + nSegments + 1;  // beginning of next ring

			for (int j = 0; j < nSegments; ++j, ++k1, ++k2)
			{
				if (i != 0)
					out_indices.insert(out_indices.end(), { k1, k2, k1 + 1 });

				if (i != (nRings - 1))
					out_indices.insert(out_indices.end(), { k1 + 1, k2, k2 + 1 });
			}
		}
	}
}


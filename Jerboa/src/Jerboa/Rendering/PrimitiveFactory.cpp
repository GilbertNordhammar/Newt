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
		int nExtraSegments = nSegments - MIN_SEGMENTS;
		int nVertices = nRings * nSegments - 1 - nExtraSegments;
		out_vertices.resize(0);
		out_vertices.reserve(nVertices * (3 + 2 + 3)); // nVertices * (pos + UV + normal)

		// top pole
		glm::vec3 pos = { 0, 1, 0 };
		glm::vec2 uv = { 0, 0 };
		glm::vec3 normal = pos;
		out_vertices.insert(out_vertices.end(), { pos.x, pos.y, pos.z, uv.x, uv.y, normal.x, normal.y, normal.z }); 

		// middle vertices
		float segmentStep = (2 * glm::pi<float>()) / nSegments;
		float ringStep = glm::pi<float>() / nRings;
		for (int i = 1; i < nRings; i++) {
			float ringAngle = glm::pi<float>() / 2 - i * ringStep;
			pos.y = glm::sin(ringAngle);
			float xz = glm::cos(ringAngle);
			
			for (int j = 0; j < nSegments; j++) {
				float sectorAngle = j * segmentStep;
				pos.z = xz * glm::sin(sectorAngle);
				pos.x = xz * glm::cos(sectorAngle);

				uv.x = (float) j / nSegments;
				uv.y = (float) i / nRings;

				normal.x = pos.x;
				normal.y = pos.y;
				normal.z = pos.z;

				out_vertices.insert(out_vertices.end(), { pos.x, pos.y, pos.z, uv.x, uv.y, normal.x, normal.y, normal.z });
			}
		}

		// bottom pole
		pos = { 0, -1, 0 };
		uv = { 1, 1 };
		normal = pos;
		out_vertices.insert(out_vertices.end(), { pos.x, pos.y, pos.z, uv.x, uv.y, normal.x, normal.y, normal.z });

		/* Generting indices */
		int nExtraRings = nRings - MIN_RINGS;
		int nTriangles = nRings * nSegments + (1 + nExtraRings) * nSegments;
		int nIndices = 3 * nTriangles;
		out_indices.resize(0);
		out_indices.reserve(nIndices);

		// first ring
		for (uint32_t i = 1; i <= nSegments; i++) {
			uint32_t iNext = i + 1;
			if (iNext > nSegments)
				iNext = 1;
			out_indices.insert(out_indices.end(), { 0, iNext, i });
		}

		// middle rings
		for (int ring = 1; ring < nRings - 1; ring++) {
			uint32_t i1 = (ring - 1) * nSegments + 1;
			uint32_t iFirst = i1;
			uint32_t iLast = ring * nSegments;
			for (int segment = 0; segment < nSegments; segment++) {
				uint32_t i2 = i1 == iLast ? iFirst : i1 + 1;
				uint32_t i3 = i1 + nSegments;
				uint32_t i4 = i2 + nSegments;

				out_indices.insert(out_indices.end(), { i1, i2, i3 });
				out_indices.insert(out_indices.end(), { i3, i2, i4 });

				i1++;
			}
		}

		// last ring
		uint32_t iLast = nVertices - 1;
		uint32_t iFirst = iLast - nSegments;
		for (uint32_t i = iFirst; i < iLast; i++) {
			uint32_t iNext = i + 1;
			if (iNext == iLast)
				iNext = iFirst;
			out_indices.insert(out_indices.end(), { iLast, i, iNext });
		}
	}
}


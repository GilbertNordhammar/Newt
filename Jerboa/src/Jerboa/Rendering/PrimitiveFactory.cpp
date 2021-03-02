#include "jerboa-pch.h"
#include "PrimitiveFactory.h"

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace Jerboa::PrimitiveFactory {
	void GenerateUVSphere(int nRings, int nSegments, float radius, glm::vec2 uvScale, std::vector<float>& out_vertices, std::vector<uint32_t>& out_indices)
	{
		const int MIN_RINGS = 3, MIN_SEGMENTS = 3;

		JERBOA_ASSERT(nRings >= MIN_RINGS, "A UV sphere can't have less than 3 rings");
		JERBOA_ASSERT(nSegments >= MIN_SEGMENTS, "A UV sphere can't have less than 3 segments");

		/* Generating vertices data (excluding tangents and bitangents) */
		int nVertices = (nRings + 1) * (nSegments + 1);
		int nDataPerVertex = 3 + 2 + 3 + 3 + 3; // position + uv + normal + tangent + bitangent
		int nVertexDatas = nVertices * nDataPerVertex;
		//out_vertices.reserve(nVertexDatas);
		out_vertices.resize(nVertexDatas);

		float segmentStep = (2 * glm::pi<float>()) / nSegments;
		float ringStep = glm::pi<float>() / nRings;
		for (int i = 0; i <= nRings; i++) {
			float ringAngle = glm::pi<float>() / 2 - i * ringStep;
			float y = glm::sin(ringAngle);
			float xz = glm::cos(ringAngle);
			
			for (int j = 0; j <= nSegments; j++) {
				float segmentAngle = 2 * glm::pi<float>() - j * segmentStep;
				float z = xz * glm::sin(segmentAngle);
				float x = xz * glm::cos(segmentAngle);

				glm::vec2 uv = { (float)j / nSegments, 1 - (float)i / nRings };
				uv *= uvScale;
				glm::vec3 normal = { x, y, z };
				glm::vec3 pos = normal * radius;

				int v = i * (nSegments + 1) * nDataPerVertex + j * nDataPerVertex;
				out_vertices[v]   = pos.x;
				out_vertices[v + 1] = pos.y;
				out_vertices[v + 2] = pos.z;
				out_vertices[v + 3] = uv.x;
				out_vertices[v + 4] = uv.y;
				out_vertices[v + 5] = normal.x;
				out_vertices[v + 6] = normal.y;
				out_vertices[v + 7] = normal.z;
				//out_vertices[v + 8] = 0; // tangent.x
				//out_vertices[v + 9] = 0; //tangent.y
				//out_vertices[v + 10] = 0; // tangent.z
				//out_vertices[v + 11] = 0; // bitangent.x
				//out_vertices[v + 12] = 0; // bitangent.y
				//out_vertices[v + 13] = 0; //bitangent.z

				//out_vertices.insert(out_vertices.end(), { pos.x, pos.y, pos.z, uv.x, uv.y, normal.x, normal.y, normal.z });
			}
		}

		/* Generting indices (plus tangents and bitangents for vertices) */
		int nExtraRings = nRings - MIN_RINGS;
		int nTriangles = nRings * nSegments + (1 + nExtraRings) * nSegments;
		int nIndices = 3 * nTriangles;
		out_indices.resize(0);
		out_indices.reserve(nIndices);

		for (int i = 0; i < nRings; ++i)
		{
			uint32_t index1 = i * (nSegments + 1);		// upper left
			uint32_t index2 = index1 + 1;				// upper right
			uint32_t index3 = index1 + nSegments + 1;	// lower left
			uint32_t index4 = index3 + 1;				// lower right

			for (int j = 0; j <= nSegments; j++, index1++, index2++, index3++, index4++)
			{
				int v1_pos = index1 * nDataPerVertex;
				int v2_pos = v1_pos + nDataPerVertex;
				int v3_pos = index3 * nDataPerVertex;
				int v4_pos = v3_pos + nDataPerVertex;

				int texCoordOffs = 3;
				int v1_uv = v1_pos + texCoordOffs;
				int v2_uv = v2_pos + texCoordOffs;
				int v3_uv = v3_pos + texCoordOffs;
				int v4_uv = v4_pos + texCoordOffs;

				int tangentOffset = 8;
				int v1_tangent = v1_pos + tangentOffset;
				int v2_tangent = v2_pos + tangentOffset;
				int v3_tangent = v3_pos + tangentOffset;
				int v4_tangent = v4_pos + tangentOffset;

				int bitangentOffset = 11;
				int v1_bitangent = v1_pos + bitangentOffset;
				int v2_bitangent = v2_pos + bitangentOffset;
				int v3_bitangent = v3_pos + bitangentOffset;
				int v4_bitangent = v4_pos + bitangentOffset;

				// triangle 1
				if (i != 0) {
					out_indices.insert(out_indices.end(), { index1, index3, index2 });
	
					auto pos1 = glm::vec3(out_vertices[v1_pos], out_vertices[v1_pos + 1], out_vertices[v1_pos + 2]);
					auto pos2 = glm::vec3(out_vertices[v2_pos], out_vertices[v2_pos + 1], out_vertices[v2_pos + 2]);
					auto pos3 = glm::vec3(out_vertices[v3_pos], out_vertices[v3_pos + 1], out_vertices[v3_pos + 2]);

					auto edge1 = pos1 - pos3;
					auto edge2 = pos2 - pos3;

					auto uv1 = glm::vec3(out_vertices[v1_uv], out_vertices[v1_uv + 1], out_vertices[v1_uv + 2]);
					auto uv2 = glm::vec3(out_vertices[v2_uv], out_vertices[v2_uv + 1], out_vertices[v2_uv + 2]);
					auto uv3 = glm::vec3(out_vertices[v3_uv], out_vertices[v3_uv + 1], out_vertices[v3_uv + 2]);

					auto deltaUV1 = uv1 - uv3;
					auto deltaUV2 = uv2 - uv3;

					float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

					glm::vec3 tangent;
					tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

					out_vertices[v1_tangent]	 = tangent.x;
					out_vertices[v1_tangent + 1] = tangent.y;
					out_vertices[v1_tangent + 2] = tangent.z;
					out_vertices[v2_tangent]	 = tangent.x;
					out_vertices[v2_tangent + 1] = tangent.y;
					out_vertices[v2_tangent + 2] = tangent.z;
					out_vertices[v3_tangent]	 = tangent.x;
					out_vertices[v3_tangent + 1] = tangent.y;
					out_vertices[v3_tangent + 2] = tangent.z;

					glm::vec3 bitangent;
					bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
					bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
					bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

					out_vertices[v1_bitangent]	   = bitangent.x;
					out_vertices[v1_bitangent + 1] = bitangent.y;
					out_vertices[v1_bitangent + 2] = bitangent.z;
					out_vertices[v2_bitangent]	   = bitangent.x;
					out_vertices[v2_bitangent + 1] = bitangent.y;
					out_vertices[v2_bitangent + 2] = bitangent.z;
					out_vertices[v3_bitangent]	   = bitangent.x;
					out_vertices[v3_bitangent + 1] = bitangent.y;
					out_vertices[v3_bitangent + 2] = bitangent.z;
				}

				// triangle 2
				if (i != (nRings - 1)) {
					out_indices.insert(out_indices.end(), { index2, index3, index4 });

					auto pos2 = glm::vec3(out_vertices[v2_pos], out_vertices[v2_pos + 1], out_vertices[v2_pos + 2]);
					auto pos3 = glm::vec3(out_vertices[v3_pos], out_vertices[v3_pos + 1], out_vertices[v3_pos + 2]);
					auto pos4 = glm::vec3(out_vertices[v4_pos], out_vertices[v4_pos + 1], out_vertices[v4_pos + 2]);

					auto edge1 = pos2 - pos3;
					auto edge2 = pos4 - pos3;

					auto uv2 = glm::vec3(out_vertices[v2_uv], out_vertices[v2_uv + 1], out_vertices[v2_uv + 2]);
					auto uv3 = glm::vec3(out_vertices[v3_uv], out_vertices[v3_uv + 1], out_vertices[v3_uv + 2]);
					auto uv4 = glm::vec3(out_vertices[v4_uv], out_vertices[v4_uv + 1], out_vertices[v4_uv + 2]);

					auto deltaUV1 = uv2 - uv3;
					auto deltaUV2 = uv4 - uv3;

					float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

					glm::vec3 tangent;
					tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

					out_vertices[v2_tangent]	 = tangent.x;
					out_vertices[v2_tangent + 1] = tangent.y;
					out_vertices[v2_tangent + 2] = tangent.z;
					out_vertices[v3_tangent]	 = tangent.x;
					out_vertices[v3_tangent + 1] = tangent.y;
					out_vertices[v3_tangent + 2] = tangent.z;
					out_vertices[v4_tangent]	 = tangent.x;
					out_vertices[v4_tangent + 1] = tangent.y;
					out_vertices[v4_tangent + 2] = tangent.z;

					glm::vec3 bitangent;
					bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
					bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
					bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

					out_vertices[v2_bitangent]	   = bitangent.x;
					out_vertices[v2_bitangent + 1] = bitangent.y;
					out_vertices[v2_bitangent + 2] = bitangent.z;
					out_vertices[v3_bitangent]	   = bitangent.x;
					out_vertices[v3_bitangent + 1] = bitangent.y;
					out_vertices[v3_bitangent + 2] = bitangent.z;
					out_vertices[v4_bitangent]	   = bitangent.x;
					out_vertices[v4_bitangent + 1] = bitangent.y;
					out_vertices[v4_bitangent + 2] = bitangent.z;
				}
			}
		}
	}
}


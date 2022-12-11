#include "jerboa-pch.h"
#include "PrimitiveFactory.h"

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace Jerboa {
	SubMeshData PrimitiveFactory::GenerateUVSphere(int rings, int segments, float radius, glm::vec2 uvScale)
	{
		SubMeshData subMesData;
		subMesData.m_VertexBufferData.m_Layout = {
				Jerboa::VertexAttributeType::Position,
				Jerboa::VertexAttributeType::TextureCoordinates1,
				Jerboa::VertexAttributeType::Normal,
				Jerboa::VertexAttributeType::Tangent
		};

		std::vector<float>& vertices = subMesData.m_VertexBufferData.m_Data;
		std::vector<uint32_t>& indices = subMesData.m_IndexBufferData.m_Data;

		const int MIN_RINGS = 3, MIN_SEGMENTS = 3;

		JERBOA_ASSERT(rings >= MIN_RINGS, "A UV sphere can't have less than 3 rings");
		JERBOA_ASSERT(segments >= MIN_SEGMENTS, "A UV sphere can't have less than 3 segments");

		/* Generating vertices data (excluding tangents) */
		int nVertices = (rings + 1) * (segments + 1);
		int nDataPerVertex = 3 + 2 + 3 + 3; // position + uv + normal + tangent
		int nVertexDatas = nVertices * nDataPerVertex;
		vertices.resize(nVertexDatas);

		float segmentStep = (2 * glm::pi<float>()) / segments;
		float ringStep = glm::pi<float>() / rings;
		for (int i = 0; i <= rings; i++) {
			float ringAngle = glm::pi<float>() / 2 - i * ringStep;
			float y = glm::sin(ringAngle);
			float xz = glm::cos(ringAngle);
			
			for (int j = 0; j <= segments; j++) {
				float segmentAngle = 2 * glm::pi<float>() - j * segmentStep;
				float z = xz * glm::sin(segmentAngle);
				float x = xz * glm::cos(segmentAngle);

				glm::vec2 uv = { (float)j / segments, 1 - (float)i / rings };
				uv *= uvScale;
				glm::vec3 normal = { x, y, z };
				glm::vec3 pos = normal * radius;

				int v = i * (segments + 1) * nDataPerVertex + j * nDataPerVertex;
				vertices[v]   = pos.x;
				vertices[v + 1] = pos.y;
				vertices[v + 2] = pos.z;
				vertices[v + 3] = uv.x;
				vertices[v + 4] = uv.y;
				vertices[v + 5] = normal.x;
				vertices[v + 6] = normal.y;
				vertices[v + 7] = normal.z;
				vertices[v + 8] = 0; // tangent.x
				vertices[v + 9] = 0; //tangent.y
				vertices[v + 10] = 0; // tangent.z
			}
		}

		/* Generting indices (plus tangents for vertices) */
		int nExtraRings = rings - MIN_RINGS;
		int nTriangles = rings * segments + (1 + nExtraRings) * segments;
		int nIndices = 3 * nTriangles;
		indices.resize(0);
		indices.reserve(nIndices);

		for (int i = 0; i < rings; ++i)
		{
			uint32_t index1 = i * (segments + 1);		// upper left
			uint32_t index2 = index1 + 1;				// upper right
			uint32_t index3 = index1 + segments + 1;	// lower left
			uint32_t index4 = index3 + 1;				// lower right

			for (int j = 0; j <= segments; j++, index1++, index2++, index3++, index4++)
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

				// triangle 1
				if (i != 0) {
					indices.insert(indices.end(), { index1, index3, index2 });
	
					auto pos1 = glm::vec3(vertices[v1_pos], vertices[v1_pos + 1], vertices[v1_pos + 2]);
					auto pos2 = glm::vec3(vertices[v2_pos], vertices[v2_pos + 1], vertices[v2_pos + 2]);
					auto pos3 = glm::vec3(vertices[v3_pos], vertices[v3_pos + 1], vertices[v3_pos + 2]);

					auto edge1 = pos1 - pos3;
					auto edge2 = pos2 - pos3;

					auto uv1 = glm::vec3(vertices[v1_uv], vertices[v1_uv + 1], vertices[v1_uv + 2]);
					auto uv2 = glm::vec3(vertices[v2_uv], vertices[v2_uv + 1], vertices[v2_uv + 2]);
					auto uv3 = glm::vec3(vertices[v3_uv], vertices[v3_uv + 1], vertices[v3_uv + 2]);

					auto deltaUV1 = uv1 - uv3;
					auto deltaUV2 = uv2 - uv3;

					float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

					glm::vec3 tangent;
					tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

					vertices[v1_tangent]	 += tangent.x;
					vertices[v1_tangent + 1] += tangent.y;
					vertices[v1_tangent + 2] += tangent.z;
					vertices[v2_tangent]	 += tangent.x;
					vertices[v2_tangent + 1] += tangent.y;
					vertices[v2_tangent + 2] += tangent.z;
					vertices[v3_tangent]	 += tangent.x;
					vertices[v3_tangent + 1] += tangent.y;
					vertices[v3_tangent + 2] += tangent.z;
				}

				// triangle 2
				if (i != (rings - 1)) {
					indices.insert(indices.end(), { index2, index3, index4 });

					auto pos2 = glm::vec3(vertices[v2_pos], vertices[v2_pos + 1], vertices[v2_pos + 2]);
					auto pos3 = glm::vec3(vertices[v3_pos], vertices[v3_pos + 1], vertices[v3_pos + 2]);
					auto pos4 = glm::vec3(vertices[v4_pos], vertices[v4_pos + 1], vertices[v4_pos + 2]);

					auto edge1 = pos2 - pos3;
					auto edge2 = pos4 - pos3;

					auto uv2 = glm::vec3(vertices[v2_uv], vertices[v2_uv + 1], vertices[v2_uv + 2]);
					auto uv3 = glm::vec3(vertices[v3_uv], vertices[v3_uv + 1], vertices[v3_uv + 2]);
					auto uv4 = glm::vec3(vertices[v4_uv], vertices[v4_uv + 1], vertices[v4_uv + 2]);

					auto deltaUV1 = uv2 - uv3;
					auto deltaUV2 = uv4 - uv3;

					float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

					glm::vec3 tangent;
					tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

					vertices[v2_tangent]	 += tangent.x;
					vertices[v2_tangent + 1] += tangent.y;
					vertices[v2_tangent + 2] += tangent.z;
					vertices[v3_tangent]	 += tangent.x;
					vertices[v3_tangent + 1] += tangent.y;
					vertices[v3_tangent + 2] += tangent.z;
					vertices[v4_tangent]	 += tangent.x;
					vertices[v4_tangent + 1] += tangent.y;
					vertices[v4_tangent + 2] += tangent.z;
				}
			}
		}

		// Normalizing tangents sums (effectively averaging them)
		for (int i = 0; i <= rings; ++i)
		{
			for (int j = 0; j <= segments; j++)
			{
				int v = i * (segments + 1) * nDataPerVertex + j * nDataPerVertex;
				
				auto tangent = glm::vec3(vertices[v + 8], vertices[v + 9], vertices[v + 10]);
				tangent = glm::normalize(tangent);
				vertices[v + 8] = tangent.x; // tangent.x
				vertices[v + 9] = tangent.y; //tangent.y
				vertices[v + 10] = tangent.z; // tangent.z
			}
		}

		return subMesData;
	}
}


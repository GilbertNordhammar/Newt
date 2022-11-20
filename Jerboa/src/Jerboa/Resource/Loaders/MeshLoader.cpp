#include "jerboa-pch.h"

#include "MeshLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Jerboa
{
	MeshLoader::MeshLoader(const GPUResourceAllocator& resourceAllocator)
		: m_ResourceAllocator(resourceAllocator)
	{
	}

	Mesh* MeshLoader::Load(std::string path, LoadConfig config)
	{
		Mesh* mesh = new Mesh();

		unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs;
		if (EnumHasFlags(config, LoadConfig::CalculateTangents))
			flags |= aiProcess_CalcTangentSpace;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, flags);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			JERBOA_LOG_ERROR("Error while loading mesh: {0}", importer.GetErrorString());
			return mesh;
		}
		else
		{
			JERBOA_LOG_INFO("Loading mesh '{0}'", path);
			m_PathToMeshGettingLoaded = path;
			ProcessNode(scene->mRootNode, scene, *mesh);
			m_PathToMeshGettingLoaded.clear();
		}

		return mesh;
	}

	void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene, Mesh& mesh)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
			mesh.AddSubMesh(CreateSubMesh(aiMesh));
		}

		// Then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, mesh);
		}
	}

	SubMesh MeshLoader::CreateSubMesh(aiMesh* aiMesh)
	{
		std::vector<VertexAttribute> vertexAttributes;
		uint32 vertexStride = 0;

		using VertexAttributeTypeInt = std::underlying_type<VertexAttributeType>::type;

		constexpr uint32 positionSize = 3;
		constexpr uint32 textureCoordSize = 2;
		constexpr uint32 normalSize = 3;
		constexpr uint32 tangentSize = 3;
		constexpr uint32 colorSize = 4;

		if (aiMesh->HasPositions())
		{
			vertexStride += positionSize;
			vertexAttributes.push_back({ VertexAttributeType::Position });
		}

		for (VertexAttributeTypeInt texCoordIndex = 0; texCoordIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES; texCoordIndex++)
		{
			if (aiMesh->HasTextureCoords(texCoordIndex))
			{
				vertexStride += textureCoordSize;
				VertexAttributeTypeInt attributeIntVal = EnumToInt(VertexAttributeType::TextureCoordinates1) * std::pow(2, texCoordIndex);
				VertexAttribute attribute = IntToEnum<VertexAttributeType>(attributeIntVal);
				vertexAttributes.push_back({ attribute });
			}
		}

		if (aiMesh->HasTextureCoords(JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES + 1))
		{
			JERBOA_LOG_WARN("Mesh '{0}' has more texture coordinates than the maximally supported {1}. The excessive ones won't get loaded. ", m_PathToMeshGettingLoaded, JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES);
		}

		if (aiMesh->HasNormals())
		{
			vertexStride += normalSize;
			vertexAttributes.push_back({ VertexAttributeType::Normal });
		}

		if (aiMesh->HasTangentsAndBitangents())
		{
			vertexStride += tangentSize;
			vertexAttributes.push_back({ VertexAttributeType::Tangent });
		}

		for (VertexAttributeTypeInt colorIndex = 0; colorIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS; colorIndex++)
		{
			if (aiMesh->HasVertexColors(colorIndex))
			{
				vertexStride += colorSize;
				VertexAttributeTypeInt attributeIntVal = EnumToInt(VertexAttributeType::Color1) * std::pow(2, colorIndex);
				VertexAttribute attribute = IntToEnum<VertexAttributeType>(attributeIntVal);
				vertexAttributes.push_back({ attribute });
			}
		}

		if (aiMesh->HasVertexColors(JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS + 1))
		{
			JERBOA_LOG_WARN("Mesh '{0}' has more vertex colors than the maximally supported {1}. The excessive ones won't get loaded. ", m_PathToMeshGettingLoaded, JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS);
		}

		VertexLayout vertexLayout = VertexLayout(vertexAttributes);

		std::vector<float> vertexBuffer;
		vertexBuffer.resize(vertexStride * aiMesh->mNumVertices);
		for (int i = 0; i < aiMesh->mNumVertices; i++)
		{
			int offset = i * vertexStride;

			if (aiMesh->HasPositions())
			{
				vertexBuffer[offset] = aiMesh->mVertices[i].x;
				vertexBuffer[offset + 1] = aiMesh->mVertices[i].y;
				vertexBuffer[offset + 2] = aiMesh->mVertices[i].z;
				offset += positionSize;
			}

			for (VertexAttributeTypeInt texCoordIndex = 0; texCoordIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES; texCoordIndex++)
			{
				if (!aiMesh->HasTextureCoords(texCoordIndex))
					break;
				vertexBuffer[offset] = aiMesh->mTextureCoords[texCoordIndex][i].x;
				vertexBuffer[offset + 1] = aiMesh->mTextureCoords[texCoordIndex][i].y;
				offset += textureCoordSize;
			}

			if (aiMesh->HasNormals())
			{
				vertexBuffer[offset] = aiMesh->mNormals[i].x;
				vertexBuffer[offset + 1] = aiMesh->mNormals[i].y;
				vertexBuffer[offset + 2] = aiMesh->mNormals[i].z;
				offset += normalSize;
			}

			if (aiMesh->HasTangentsAndBitangents())
			{
				vertexBuffer[offset] = aiMesh->mTangents[0].x;
				vertexBuffer[offset + 1] = aiMesh->mTangents[0].y;
				vertexBuffer[offset + 2] = aiMesh->mTangents[0].z;
				offset += tangentSize;
			}

			for (VertexAttributeTypeInt colorIndex = 0; colorIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS; colorIndex++)
			{
				if (!aiMesh->HasVertexColors(colorIndex))
					break;
				vertexBuffer[offset] = aiMesh->mColors[colorIndex][i].r;
				vertexBuffer[offset + 1] = aiMesh->mColors[colorIndex][i].g;
				vertexBuffer[offset + 2] = aiMesh->mColors[colorIndex][i].b;
				vertexBuffer[offset + 3] = aiMesh->mColors[colorIndex][i].a;
				offset += colorSize;
			}
		}
		
		std::vector<uint32> indexBuffer = std::vector<uint32>();
		if (aiMesh->HasFaces())
		{
			for (int i = 0; i < aiMesh->mNumFaces; i++)
			{
				for (int j = 0; j < aiMesh->mFaces[i].mNumIndices; j++)
				{
					indexBuffer.push_back(aiMesh->mFaces[i].mIndices[j]);
				}
			}
		}

		IndexBufferData* indexBufferData = nullptr;
		if (indexBuffer.size() > 0)
		{
			indexBufferData = new IndexBufferData(indexBuffer.data(), indexBuffer.size() * sizeof(indexBuffer[0]));
		}

		SubMesh subMesh;
		VertexBufferData vertexBufferData = VertexBufferData(vertexBuffer.data(), vertexBuffer.size() * sizeof(vertexBuffer[0]), VertexBufferUsage::Static, vertexLayout);
		subMesh.Create(vertexBufferData, indexBufferData, PrimitiveType::Triangle, m_ResourceAllocator);

		delete indexBufferData;
		return subMesh;
	}
}
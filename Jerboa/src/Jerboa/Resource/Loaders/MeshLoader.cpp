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
		VertexBufferData vertexBufferData = VertexBufferData(vertexLayout);

		vertexBufferData.m_Data.resize(vertexStride * aiMesh->mNumVertices);
		for (int i = 0; i < aiMesh->mNumVertices; i++)
		{
			int offset = i * vertexStride;

			if (aiMesh->HasPositions())
			{
				vertexBufferData.m_Data[offset] = aiMesh->mVertices[i].x;
				vertexBufferData.m_Data[offset + 1] = aiMesh->mVertices[i].y;
				vertexBufferData.m_Data[offset + 2] = aiMesh->mVertices[i].z;
				offset += positionSize;
			}

			for (VertexAttributeTypeInt texCoordIndex = 0; texCoordIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES; texCoordIndex++)
			{
				if (!aiMesh->HasTextureCoords(texCoordIndex))
					break;
				vertexBufferData.m_Data[offset] = aiMesh->mTextureCoords[texCoordIndex][i].x;
				vertexBufferData.m_Data[offset + 1] = aiMesh->mTextureCoords[texCoordIndex][i].y;
				offset += textureCoordSize;
			}

			if (aiMesh->HasNormals())
			{
				vertexBufferData.m_Data[offset] = aiMesh->mNormals[i].x;
				vertexBufferData.m_Data[offset + 1] = aiMesh->mNormals[i].y;
				vertexBufferData.m_Data[offset + 2] = aiMesh->mNormals[i].z;
				offset += normalSize;
			}

			if (aiMesh->HasTangentsAndBitangents())
			{
				vertexBufferData.m_Data[offset] = aiMesh->mTangents[0].x;
				vertexBufferData.m_Data[offset + 1] = aiMesh->mTangents[0].y;
				vertexBufferData.m_Data[offset + 2] = aiMesh->mTangents[0].z;
				offset += tangentSize;
			}

			for (VertexAttributeTypeInt colorIndex = 0; colorIndex < JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS; colorIndex++)
			{
				if (!aiMesh->HasVertexColors(colorIndex))
					break;
				vertexBufferData.m_Data[offset] = aiMesh->mColors[colorIndex][i].r;
				vertexBufferData.m_Data[offset + 1] = aiMesh->mColors[colorIndex][i].g;
				vertexBufferData.m_Data[offset + 2] = aiMesh->mColors[colorIndex][i].b;
				vertexBufferData.m_Data[offset + 3] = aiMesh->mColors[colorIndex][i].a;
				offset += colorSize;
			}
		}
		
		IndexBufferData indexBufferData;
		if (aiMesh->HasFaces())
		{
			for (int i = 0; i < aiMesh->mNumFaces; i++)
			{
				for (int j = 0; j < aiMesh->mFaces[i].mNumIndices; j++)
				{
					indexBufferData.m_Data.push_back(aiMesh->mFaces[i].mIndices[j]);
				}
			}
		}

		SubMesh subMesh;
		subMesh.Create(vertexBufferData, &indexBufferData, PrimitiveType::Triangle, m_ResourceAllocator);

		return subMesh;
	}
}
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

	Mesh* MeshLoader::Load(std::string path)
	{
		Mesh* mesh = new Mesh();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			JERBOA_LOG_ERROR("Error while loading mesh: {0}", importer.GetErrorString());
			return mesh;
		}
		else
		{
			ProcessNode(scene->mRootNode, scene, *mesh);
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
		std::vector<VertexAttribute> vertexAttribues;
		uint32 vertexStride = 0;

		constexpr uint32 positionSize = 3;
		constexpr uint32 textureCoordSize = 2;
		constexpr uint32 normalSize = 3;
		constexpr uint32 tangentSize = 3;
		constexpr uint32 bitangentSize = 3;
		constexpr uint32 colorSize = 4;

		if (aiMesh->HasPositions())
		{
			vertexStride += positionSize;
			vertexAttribues.push_back({ VertexAttributeType::Position });
		}

		if (aiMesh->HasTextureCoords(0))
		{
			vertexStride += textureCoordSize;
			vertexAttribues.push_back({ VertexAttributeType::TextureCoordinates });
		}

		if (aiMesh->HasNormals())
		{
			vertexStride += normalSize;
			vertexAttribues.push_back({ VertexAttributeType::Normal });
		}

		if (aiMesh->HasTangentsAndBitangents())
		{
			vertexStride += tangentSize + bitangentSize;
			vertexAttribues.push_back({ VertexAttributeType::Tangent });
			vertexAttribues.push_back({ VertexAttributeType::Bitangent });
		}

		if (aiMesh->HasVertexColors(0))
		{
			vertexStride += colorSize;
			vertexAttribues.push_back({ VertexAttributeType::Color });
		}

		VertexLayout vertexLayout = VertexLayout(vertexAttribues);

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

			if (aiMesh->HasTextureCoords(0))
			{
				vertexBuffer[offset] = aiMesh->mTextureCoords[0][i].x;
				vertexBuffer[offset + 1] = aiMesh->mTextureCoords[0][i].y;
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

				vertexBuffer[offset] = aiMesh->mBitangents[0].x;
				vertexBuffer[offset + 1] = aiMesh->mBitangents[0].y;
				vertexBuffer[offset + 2] = aiMesh->mBitangents[0].z;
				offset += bitangentSize;
			}

			if (aiMesh->HasVertexColors(0))
			{
				vertexBuffer[offset] = aiMesh->mColors[0]->r;
				vertexBuffer[offset + 1] = aiMesh->mColors[0]->g;
				vertexBuffer[offset + 2] = aiMesh->mColors[0]->b;
				vertexBuffer[offset + 3] = aiMesh->mColors[0]->a;
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
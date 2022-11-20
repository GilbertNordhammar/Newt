#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

#include "Jerboa/Core/Bit.h"
#include "Jerboa/Core/Enum.h"

#include <assimp/scene.h>
#include <string>
#include <vector>

namespace Jerboa
{
	class MeshLoader
	{
	public:
		enum class LoadConfig
		{
			None = 0,
			CalculateTangents = BITMASK_1
		};

		MeshLoader(const GPUResourceAllocator& resourceAllocator);
		Mesh* Load(std::string path, LoadConfig config = LoadConfig::None);
		
	private:
		void ProcessNode(aiNode* node, const aiScene* scene, Mesh& mesh);
		SubMesh CreateSubMesh(aiMesh* aiMesh);

		const GPUResourceAllocator& m_ResourceAllocator;
		std::string m_PathToMeshGettingLoaded = "";
	};

	JERBOA_ENABLE_ENUM_FLAG_OPERATORS(MeshLoader::LoadConfig);
}
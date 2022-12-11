#include "Jerboa/Rendering/Resource/Data/MeshData.h"

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

		MeshData Load(std::string path, LoadConfig config = LoadConfig::None);
		
	private:
		void ProcessNode(aiNode* node, const aiScene* scene, MeshData& mesh);
		SubMeshData CreateSubMeshData(aiMesh* aiMesh);

		std::string m_PathToMeshGettingLoaded = "";
	};

	JERBOA_ENABLE_ENUM_FLAG_OPERATORS(MeshLoader::LoadConfig);
}
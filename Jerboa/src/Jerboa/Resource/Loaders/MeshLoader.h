#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"
#include <assimp/scene.h>

#include <string>
#include <vector>

namespace Jerboa
{
	class MeshLoader
	{
	public:
		MeshLoader(const GPUResourceAllocator& resourceAllocator);
		Mesh* Load(std::string path);
		
	private:
		void ProcessNode(aiNode* node, const aiScene* scene, Mesh& mesh);
		SubMesh CreateSubMesh(aiMesh* aiMesh);

		const GPUResourceAllocator& m_ResourceAllocator;
	};
}
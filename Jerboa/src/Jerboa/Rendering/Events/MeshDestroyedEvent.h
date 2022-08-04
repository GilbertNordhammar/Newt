#pragma once

#include "Jerboa/Core/Event.h"
#include "Jerboa/Rendering/Resource/Mesh.h"

namespace Jerboa {
	struct MeshDestroyedEvent : Event 
	{
		MeshDestroyedEvent(const Mesh& mesh)
			: m_Mesh(mesh) 
		{
		}

		const Mesh& m_Mesh;
	};
}
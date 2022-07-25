#pragma once

#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/GPUResourceAllocator.h"
#include "Jerboa/Rendering/Mesh.h"
#include "Jerboa/Rendering/RenderState.h"
#include "Jerboa/Rendering/Shader.h"
#include "Jerboa/Rendering/Texture.h"
#include "Jerboa/Rendering/Types.h"

#include <memory>

namespace Jerboa {
	class Mesh;

	class Renderer
	{
	public:
		static Renderer* Create();
		virtual ~Renderer() {};

		virtual void			Clear() = 0;
		virtual void			Draw(Mesh& mesh) = 0;

		RenderState*			GetState() { return m_RenderState.get(); }
		GPUResourceAllocator*	GetAllocator() { return m_Allocator.get(); }
	protected:
		std::shared_ptr<RenderState>			m_RenderState;
		std::shared_ptr<GPUResourceAllocator>	m_Allocator;
	};
}



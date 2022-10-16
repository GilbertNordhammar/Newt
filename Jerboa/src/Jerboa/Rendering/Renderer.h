#pragma once

#include "Jerboa/Core/Singleton.h"
#include "Jerboa/Core/Types.h"
#include "Jerboa/Rendering/RenderState.h"
#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Resource/Shader.h"
#include "Jerboa/Rendering/Resource/Texture.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"
#include "Jerboa/Rendering/ShaderState.h"
#include "Jerboa/Rendering/Types.h"

#include <memory>

namespace Jerboa {
	class Mesh;

	class Renderer : Singleton<Renderer>
	{
	public:
		static Renderer*		Create();
		virtual					~Renderer() {};

		virtual void			BeginFrame();
		virtual void			EndFrame();

		virtual void			Draw(Mesh& mesh);
		virtual void			Draw(const SubMesh& mesh) = 0;
		
		RenderState&			GetState()			{ return *m_RenderState.get(); }
		ShaderState&			GetShaderState()	{ return *m_ShaderState.get(); }
		GPUResourceAllocator&	GetAllocator()		{ return *m_Allocator.get(); }
		
		RenderState*			GetStatePtr()		{ return m_RenderState.get(); }
		ShaderState*			GetShaderStatePtr() { return m_ShaderState.get(); }
		GPUResourceAllocator*	GetAllocatorPtr()	{ return m_Allocator.get(); }

	protected:
		virtual void			BeginFrameImpl() = 0;
		virtual void			EndFrameImpl() = 0;

		std::shared_ptr<RenderState>			m_RenderState = nullptr;
		std::shared_ptr<ShaderState>			m_ShaderState = nullptr;
		std::shared_ptr<GPUResourceAllocator>	m_Allocator = nullptr;
	};
}



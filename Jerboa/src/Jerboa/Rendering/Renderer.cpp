#include "jerboa-pch.h"
#include "Renderer.h"


#if defined(JERBOA_RENDER_API_OPENGL)
#include "Jerboa/Platform/OpenGL/GL_Renderer.h"
#endif

namespace Jerboa {
	Renderer* Renderer::Create()
	{


		Renderer* renderer;
#if defined(JERBOA_RENDER_API_OPENGL)
		renderer = new GL_Renderer();
#else
#error "JERBOA_RENDER_API_ is not defined"
#endif
		renderer->m_RenderState = std::shared_ptr<RenderState>(RenderState::Create());
		JERBOA_ASSERT(renderer->m_RenderState, "Render state is null");

		return renderer;
	}
}

#include "jerboa-pch.h"
#include "Renderer.h"

#if defined(JERBOA_RENDER_API_OPENGL)
#include "Jerboa/Platform/OpenGL/GL_GPUResourceAllocator.h"
#include "Jerboa/Platform/OpenGL/GL_Renderer.h"
#include "Jerboa/Platform/OpenGL/GL_RenderState.h"
#endif

namespace Jerboa {
	Renderer* Renderer::Create()
	{
		Renderer* renderer;
#if defined(JERBOA_RENDER_API_OPENGL)
		auto renderState = std::make_shared<GL_RenderState>();
		renderer = new GL_Renderer(renderState.get());
		renderer->m_RenderState = renderState;
		renderer->m_Allocator = std::make_shared<GL_GPUResourceAllocator>(renderState.get());
#else
#error "JERBOA_RENDER_API_ is not defined"
#endif
		JERBOA_ASSERT(renderer->m_RenderState, "Render state is null");
		JERBOA_ASSERT(renderer->m_Allocator, "GPU resource allocator is null");

		return renderer;
	}
}

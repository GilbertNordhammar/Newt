#include "jerboa-pch.h"
#include "Renderer.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa {
	void Renderer::BeginPass()
	{
	
	}
	
	void Renderer::EndPass()
	{
	
	}
	
	void Renderer::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	
	void Renderer::Submit(std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		// TODO
	}

	void Renderer::Draw(int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}
}

#include "jerboa-pch.h"
#include "GL_Renderer.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Mesh.h"
#include "Jerboa/Rendering/RenderState.h"

namespace Jerboa {
	void GL_Renderer::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GL_Renderer::Draw(Mesh& mesh)
	{
		mesh.Bind();

		if (mesh.IsIndexed())
		{
			glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			// glDrawArays
		}
	}
}
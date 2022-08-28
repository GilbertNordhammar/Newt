#include "jerboa-pch.h"
#include "GL_Renderer.h"

#include "Jerboa/Core/Types.h"
#include "Jerboa/Platform/OpenGL/GL_RenderState.h"
#include "Jerboa/Platform/OpenGL/GL_Types.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Resource/Mesh.h"

namespace Jerboa {
	static GLenum ConvertPritimtiveTypeToGL(PrimitiveType primitiveType)
	{
		switch (primitiveType)
		{
			case Jerboa::PrimitiveType::Points:			return GL_POINTS;
			case Jerboa::PrimitiveType::Lines:			return GL_LINES;
			case Jerboa::PrimitiveType::LineStrip:		return GL_LINE_STRIP;
			case Jerboa::PrimitiveType::Triangle:		return GL_TRIANGLES;
			case Jerboa::PrimitiveType::TriangleStrip:	return GL_TRIANGLE_STRIP;
		}

		JERBOA_ASSERT(false, "Invalid or unhandled PrimitiveType entry");
		return GL_INVALID_ENUM;
	}


	GL_Renderer::GL_Renderer(GL_RenderState* renderStateGL)
		: m_RenderStateGL(renderStateGL)
	{
		JERBOA_ASSERT(renderStateGL, "Render state is null");
		m_EventObserver.Subscribe(this, &GL_Renderer::OnWindowResize);
	}

	void GL_Renderer::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GL_Renderer::Draw(Mesh& mesh)
	{
		Mesh* boundMesh = m_RenderState->GetBoundMesh();
		if (!boundMesh || boundMesh != &mesh || m_RenderStateGL->m_BoundMeshStateDirty)
		{
			m_RenderState->BindMesh(mesh);
			m_RenderStateGL->m_BoundMeshStateDirty = false;
		}

		if (mesh.IsIndexed())
		{
			glDrawElements(ConvertPritimtiveTypeToGL(mesh.GetPrimitiveType()), mesh.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(ConvertPritimtiveTypeToGL(mesh.GetPrimitiveType()), 0, mesh.GetVertexBuffer()->GetCount());
		}
	}

	void GL_Renderer::OnWindowResize(const WindowResizeEvent& evnt)
	{
		glViewport(0, 0, evnt.width, evnt.height); // TODO: Remove explicit OpenGL call
	}
}
#include "jerboa-pch.h"
#include "GL_Renderer.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Mesh.h"
#include "Jerboa/Rendering/RenderState.h"

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
			glDrawElements(ConvertPritimtiveTypeToGL(mesh.GetPrimitiveType()), mesh.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(ConvertPritimtiveTypeToGL(mesh.GetPrimitiveType()), 0, mesh.GetVertexBuffer()->GetCount());
		}
	}
}
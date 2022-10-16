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
	}

	void GL_Renderer::Draw(const SubMesh& subMesh)
	{
		uint32 newVAO = subMesh.GetVAO().Get();
		if (m_RenderStateGL->m_BoundVAO != newVAO)
		{
			glBindVertexArray(newVAO);
			m_RenderStateGL->m_BoundVAO = newVAO;
		}

		if (subMesh.IsIndexed())
		{
			glDrawElements(ConvertPritimtiveTypeToGL(subMesh.GetPrimitiveType()), subMesh.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(ConvertPritimtiveTypeToGL(subMesh.GetPrimitiveType()), 0, subMesh.GetVertexBuffer()->GetCount());
		}
	}

	void GL_Renderer::BeginFrameImpl()
	{
		
	}

	void GL_Renderer::EndFrameImpl()
	{
		m_RenderState->BeginDefaultRenderPass();
		auto clearColor = m_RenderState->GetClearColor();
		auto clearBits = ConvertBufferClearBitsToGL(m_RenderState->GetClearBits());
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(clearBits);
	}
}
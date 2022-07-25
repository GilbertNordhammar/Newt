#include "jerboa-pch.h"
#include "GL_GPUResourceAllocator.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/OpenGL/GL_RenderState.h"
#include "Jerboa/Platform/OpenGL/GL_Types.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa
{
	GL_GPUResourceAllocator::GL_GPUResourceAllocator(GL_RenderState* renderState)
		: m_RenderStateGL(renderState)
	{
		JERBOA_ASSERT(renderState, "Render state is null");
	}

	GPUResource GL_GPUResourceAllocator::CreateVertexBuffer(const VertexBufferData& bufferData)
	{
		auto generateVertexBuffer = [&](uint64* vertexBufferObject)
		{
			GLuint glObject = 0;
			glGenBuffers(1, &glObject);
			*vertexBufferObject = glObject;

			glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, bufferData.m_Size, bufferData.m_Data, GetOpenGLUsage(bufferData.m_Usage));

			VertexBufferLayout layout = bufferData.m_Layout;
			int index = 0;
			for (auto& elem : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					elem.ComponentCount,
					GetOpenGLBaseType(elem.Type),
					elem.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(void*)elem.Offset);
				index++;
			}
		};

		auto deleteVertexBuffer = [](uint64* vertexBufferObject) {
			GLuint glObject = *vertexBufferObject;
			glDeleteBuffers(1, &glObject);
		};

		GPUResource vertexBuffer;
		vertexBuffer.Create(generateVertexBuffer, deleteVertexBuffer);
		return vertexBuffer;
	}

	GPUResource GL_GPUResourceAllocator::CreateIndexBuffer(const IndexBufferData& bufferData)
	{
		auto generateIndexBuffer = [&](uint64* indexBufferObject)
		{
			GLuint glObject = 0;
			glGenBuffers(1, &glObject);
			*indexBufferObject = glObject;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferData.m_Size, bufferData.m_Data, GL_STATIC_DRAW); // Might make usage a variable in the future
			
		};

		auto deleteIndexBuffer = [](uint64* indexBufferObject) {
			GLuint glObject = *indexBufferObject;
			glDeleteBuffers(1, &glObject);
		};

		GPUResource indexBuffer;
		indexBuffer.Create(generateIndexBuffer, deleteIndexBuffer);
		return indexBuffer;
	}

	GPUResource GL_GPUResourceAllocator::CreateVertexArrayObject()
	{
		auto generateVAO = [&](uint64* vao)
		{
			GLuint glObject = 0;
			glGenVertexArrays(1, &glObject);
			*vao = glObject;
			glBindVertexArray(*vao);
			m_RenderStateGL->m_BoundMeshStateDirty = true;
		};

		auto deleteVAO = [](uint64* vao) {
			GLuint glObject = *vao;
			glDeleteVertexArrays(1, &glObject);
		};

		GPUResource VAO;
		VAO.Create(generateVAO, deleteVAO);
		return VAO;
	}
}
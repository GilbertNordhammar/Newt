#include "jerboa-pch.h"
#include "OpenGL_VertexBuffer.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	static GLenum GetOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}
		JERBOA_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static GLenum GetOpenGLUsage(VertexBufferUsage usage) {
		switch (usage) {
			case VertexBufferUsage::Dynamic:	return GL_DYNAMIC_DRAW;
			case VertexBufferUsage::Static:		return GL_STATIC_DRAW;
		}

		JERBOA_ASSERT(false, "Unknown usage!");
		return 0;
	}

	OpenGL_VertexBuffer::OpenGL_VertexBuffer(void* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GetOpenGLUsage(usage));

		int index = 0;
		for (auto& elem : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				elem.ComponentCount, 
				GetOpenGLBaseType(elem.Type), 
				elem.Normalized ? GL_TRUE : GL_FALSE, 
				elem.Size, 
				(void *) elem.Offset
			);
		}
	}
	void OpenGL_VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	}
	void OpenGL_VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGL_VertexBuffer::SetLayout()
	{
	}
}


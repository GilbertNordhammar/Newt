#include "jerboa-pch.h"
#include "OpenGL_IndexBuffer.h"

#include <glad/glad.h>

namespace Jerboa {
	Jerboa::OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* data, uint32_t size)
		: mSize(size), mCount(mSize / sizeof(uint32_t))
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // Might make usage a variable in the future
	}

	void OpenGL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
	}

	void Jerboa::OpenGL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

